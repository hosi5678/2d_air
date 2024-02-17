import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

from count_csv_files import count_csv_files
from shell_command import shell_command

# csv filesのフォルダパス
csv_dir="./ez_timestep_csvs/"

# csvのファイル数の取得
timestep = count_csv_files(csv_dir)

# 出力するフレーム数の入力
timestep = int(input("input timestep number.(>0)"))

for i in range(timestep):
    
    # 6桁固定のiを作り出す
    fmt_i = '{:06d}'.format(i)
    csv_file=csv_dir+"ez_timestep_"+fmt_i+".csv"

    # data frameに読み込む
    df=pd.read_csv(csv_file)

    # x軸のデータ（1行目）

    # DataFrameを転置する（行と列を入れ替える）
    # 折れ線グラフは縦方向に転置し、heatmapは横方向に読み込む

    # figure(全体図)のサイズをfull hdに設定
    fig=plt.figure(figsize=(1300/80,1080/80),dpi=80)

    fig.suptitle('Heatmap of Ez',fontsize=20)

    
    # heatmapにもx軸を設定する。間隔はxticklabels=5で設定する。
    heatmap=sns.heatmap(df, xticklabels=5, yticklabels=5,cmap='coolwarm',cbar=True,center=0.0)
    heatmap.invert_yaxis()

    heatmap.set_xlabel('x position' , {"fontsize":15})
    
    heatmap.set_ylabel('y position' ,{"fontsize":15} )
    
    plt.suptitle("timestep="+str(i),fontsize=25)
    
    # ファイルを保存
    plt.savefig("./pngs/png_"+fmt_i+".png")
    
    # saveの表示
    print("./pngs/png_"+fmt_i+".png"+"/"+str(timestep)+" was created.")
    
    # csv fileの削除
    os.unlink(csv_file)
    
    # メモリの解放
    plt.clf()
    plt.close()

# 最後は下記のコマンドで動画ができる。
# ffmpeg -r 10 -i ../pngs/png_%06d.png -c:v libx264 -pix_fmt yuv420p output.mp4


# 後処理
command="rm ./mp4/output.mp4"
shell_command(command)

command="ffmpeg -r 10 -i ./pngs/png_%06d.png -c:v libx264 -pix_fmt yuv420p ./mp4/output.mp4"
shell_command(command)    

command="vlc ./mp4/output.mp4"
shell_command(command)

command="rm -rf ./pngs/*.png"
shell_command(command)

command="rm -rf ./ey_timestep_csvs/*.csv"
shell_command(command)

command="rm -rf ./ez_graph_csvs/*.csv"
shell_command(command)
