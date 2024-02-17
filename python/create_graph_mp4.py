# 1つのグラフの動画を求めるpythonプログラム
import os
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

from count_csv_files import count_csv_files
from shell_command import shell_command

# csv filesのフォルダパス
csv_dir="./ez_graph_csvs/"

# csvのファイル数の取得
timestep = count_csv_files(csv_dir)

print(str(timestep)+" csv files were found.")

# eyの最大値、最小値の取得
ey_range_file="./csv_files/ez_range.csv"

df=pd.read_csv(ey_range_file,header=None)

print("ey_max="+str(df.iloc[0].max()))
print("ey_min="+str(df.iloc[1].min()))

ez_max=df.iloc[0].max()
ez_min=df.iloc[1].min()

# hzの最大値、最小値の取得
# hz_range_file="./csv_files/hz_range.csv"

# df=pd.read_csv(hz_range_file,header=None)

# print("hz_max="+str(df.iloc[0].max()))
# print("hz_min="+str(df.iloc[1].min()))

# hzの最大値、最小値の取得
# hz_max=df.iloc[0].max()
# hz_min=df.iloc[1].min()

timestep = int(input("input timestep number(>0)."))

for i in range(timestep):
    
    # 6桁固定のiを作り出す
    fmt_i = '{:06d}'.format(i)
    csv_file="./ez_graph_csvs/ez_graph_timestep_"+fmt_i+".csv"
    
    # data frameに読み込む
    df_ez=pd.read_csv(csv_file,header=None)
    
    # x軸のデータ（1行目）
    xticks = df_ez.iloc[0]

    # データ部分（2行目以降）
    data = df_ez.iloc[1:]

    # DataFrameを転置する（行と列を入れ替える）
    # 折れ線グラフは縦方向に転置し、heatmapは横方向に読み込む

    # figure(全体図)のサイズをfull hdに設定
    fig=plt.figure(figsize=(1920/80,1080/80),dpi=80)

    # 2行1列の1行目
    
    plt.title('Ez Amplitude',{"fontsize":20})
    
    plt.xlabel('x position',{"fontsize":15})
    plt.ylabel('Ez amplitude',{"fontsize":15})
 
    plt.xlim(left=0)
    plt.xlim(right=len(xticks))

    plt.xticks( np.arange(0, len(xticks), 5) )
    # ax1.set_yticks( np.arange(min , max , 0.0000025) )

    plt.ylim(top=ez_max)
    plt.ylim(bottom=ez_min)

    # 折れ線グラフのプロット
    plt.plot(df_ez.T,color="blue")
    
    # # csv fileの削除
    # os.unlink(csv_file)

    # # hz成分
    # # 2行1列の2行目
    # ax2=fig.add_subplot(2,1,2)

    # csv_file="./hz_timestep_csvs/hz_timestep_"+fmt_i+".csv"
        
    # # data frameに読み込む
    # df_hz=pd.read_csv(csv_file,header=None)
    
    # # print(df_hz)
    
    # # x軸のデータ（1行目）
    # xticks = df_hz.iloc[0]

    # # データ部分（2行目以降）
    # data = df_hz.iloc[1:]
    
    # ax2.set_title('Hz Amplitude',{"fontsize":20})
    
    # ax2.set_xlabel('x position',{"fontsize":15})
    # ax2.set_ylabel('Hz amplitude',{"fontsize":15})
 
    # ax2.set_xlim(left=0)
    # ax2.set_xlim(right=len(xticks))

    # ax2.set_xticks( np.arange(0, len(xticks), 5) )
    
    # ax2.set_ylim(top=hz_max)
    # ax2.set_ylim(bottom=hz_min)

    # ax2.plot(df_hz.T,color="blue")

    # # heatmapにもx軸を設定する。間隔はxticklabels=5で設定する。
    # # heatmap=sns.heatmap(data, xticklabels=5, yticklabels=False,cmap='coolwarm',cbar=False,center=0.0)
    # # # ax2.xaxis.set_major_locator(ticker.MultipleLocator(5)) 
    # # heatmap.set_xlabel('x position' , {"fontsize":15})
    
    plt.suptitle("timestep="+str(i),fontsize=25)
    # plt.tight_layout()

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
    
command="rm -rf ./pngs/*.png"
shell_command(command)

command="vlc ./mp4/output.mp4"
shell_command(command)

command="rm -rf ./ey_timestep_csvs/*.csv"
shell_command(command)

command="rm -rf ./hz_timestep_csvs/*.csv"
shell_command(command)

command="rm -rf ./ez_graph_csvs/*.csv"
shell_command(command)
