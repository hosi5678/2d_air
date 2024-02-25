import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule

from count_csv_files import count_csv_files
from shell_command import shell_command

WIDTH=100
HEIGHT=100

# CUDAカーネルの定義
cuda_kernel = """
#include <stdio.h>

#define WIDTH 100  // データの幅
#define HEIGHT 100  // データの高さ

__global__ void heatmap_kernel(float *data, int timestep) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    int idy = threadIdx.y + blockIdx.y * blockDim.y;
    int index = idy * WIDTH + idx;

    // 各スレッドが担当するデータを取得
    float value = data[index];

    // ここでヒートマップの計算を行う

    // ヒートマップの結果をdataに書き戻す
    data[index] = value;
}

"""

# CUDAカーネルをコンパイル
mod = SourceModule(cuda_kernel)
heatmap_kernel = mod.get_function("heatmap_kernel")

# csv filesのフォルダパス
csv_dir = "./ez_timestep_csvs/"

# csvのファイル数の取得
timestep = count_csv_files(csv_dir)

# 出力するフレーム数の入力
timestep = int(input("input timestep number.(>0)"))

for i in range(timestep):
    # 6桁固定のiを作り出す
    fmt_i = '{:06d}'.format(i)
    csv_file = csv_dir + "ez_timestep_" + fmt_i + ".csv"

    # data frameに読み込む
    df = pd.read_csv(csv_file)

    # GPU用のデータを作成
    data = np.array(df.values, dtype=np.float32)
    data_gpu = cuda.mem_alloc(data.nbytes)
    cuda.memcpy_htod(data_gpu, data)

    # CUDAカーネルの実行
    block_size = (32, 32, 1)
    grid_size = (WIDTH // block_size[0], HEIGHT // block_size[1])
    heatmap_kernel(data_gpu, np.int32(i), block=block_size, grid=grid_size)

    # 結果を取得
    cuda.memcpy_dtoh(data, data_gpu)

    # 結果をヒートマップとして描画
    plt.figure(figsize=(13, 10))
    plt.imshow(data, cmap='coolwarm', interpolation='nearest')
    plt.colorbar()
    plt.xlabel('x position')
    plt.ylabel('y position')
    plt.title("Heatmap of Ez (Timestep {})".format(i))
    plt.savefig("./pngs/png_" + fmt_i + ".png")
    plt.close()

    # saveの表示
    print("./pngs/png_" + fmt_i + ".png/" + str(timestep) + " was created.")

    # csv fileの削除
    os.unlink(csv_file)

# 最後は下記のコマンドで動画ができる。
# ffmpeg -r 10 -i ../pngs/png_%06d.png -c:v libx264 -pix_fmt yuv420p output.mp4

# 後処理
command = "rm ./mp4/output.mp4"
shell_command(command)

command = "ffmpeg -r 10 -i ./pngs/png_%06d.png -c:v libx264 -pix_fmt yuv420p ./mp4/output.mp4"
shell_command(command)

command = "vlc ./mp4/output.mp4"
shell_command(command)

command = "rm -rf ./pngs/*.png"
shell_command(command)

command = "rm -rf ./ey_timestep_csvs/*.csv"
shell_command(command)

command = "rm -rf ./ez_graph_csvs/*.csv"
shell_command(command)
