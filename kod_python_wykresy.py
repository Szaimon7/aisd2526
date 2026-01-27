import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


data_lcs = {
    'N': [10, 20, 100, 500, 1000, 2000, 5000],
    'LCS_Iter': [12, 25, 351, 7315, 25661, 106140, 671220],
    'LCS_Rekur': [4, 18, 336, 8902, 36635, 160513, 1132166]
}


data_huffman = {
    'N': [100, 1000, 10000, 100000, 500000, 1000000],
    'Huffman_Time': [30, 48, 40, 41, 44, 45]
}


data_activity = {
    'N': [30, 100, 200, 500, 1000, 3000, 5000, 8000],
    'Activity_Naiwny': [1, 2, 3, 7, 12, 34, None, None], # None dla pustych pól
    'Activity_DP': [4, 45, 188, 1151, 4176, 31900, 85908, 242606],
    'Activity_Iter': [0, 1, 3, 7, 9, 22, 41, 58]
}


data_cutrod = {
    'N': [10, 20, 25, 30, 100, 500, 1000, 2000],
    'CutRod_Naiwny': [13, 10182, 289866, None, None, None, None, None],
    'CutRod_Spam': [2, 7, 8, 8, 81, 1602, 5790, 18819],
    'CutRod_Iter': [1, 2, 4, 5, 43, 708, 3363, 10312]
}


df_lcs = pd.DataFrame(data_lcs).melt('N', var_name='Algorytm', value_name='Czas (us)')
df_huff = pd.DataFrame(data_huffman).melt('N', var_name='Algorytm', value_name='Czas (us)')
df_act = pd.DataFrame(data_activity).melt('N', var_name='Algorytm', value_name='Czas (us)')
df_rod = pd.DataFrame(data_cutrod).melt('N', var_name='Algorytm', value_name='Czas (us)')


df_lcs['Problem'] = 'LCS'
df_huff['Problem'] = 'Huffman'
df_act['Problem'] = 'Activity Selection'
df_rod['Problem'] = 'Rod Cutting'


final_table = pd.concat([df_lcs, df_huff, df_act, df_rod], ignore_index=True)


pivot_table = final_table.pivot_table(index='N', columns=['Problem', 'Algorytm'], values='Czas (us)')

print(" zbiorcza tabela czasów")

print(pivot_table.fillna('-').to_string())



plt.style.use('seaborn-v0_8-whitegrid')
fig, axs = plt.subplots(2, 2, figsize=(16, 12))
fig.suptitle('Porównanie Wydajności Algorytmów (czas w µs)', fontsize=20, weight='bold')


ax1 = axs[0, 0]
ax1.plot(data_lcs['N'], data_lcs['LCS_Iter'], marker='o', label='Iteracyjny')
ax1.plot(data_lcs['N'], data_lcs['LCS_Rekur'], marker='x', label='Rekurencyjny', linestyle='--')
ax1.set_title('LCS')
ax1.set_xlabel('N')
ax1.set_ylabel('Czas (us)')
ax1.legend()
ax1.grid(True)


ax2 = axs[0, 1]
ax2.plot(data_huffman['N'], data_huffman['Huffman_Time'], marker='s', color='green', label='Huffman')
ax2.set_title('Huffman Coding (Złożoność zależna od alfabetu)')
ax2.set_xlabel('N (Długość tekstu)')
ax2.set_ylabel('Czas (us)')
ax2.legend()
ax2.grid(True)

ax2.ticklabel_format(style='plain', axis='x') 


ax3 = axs[1, 0]

n_naive_act = [n for n, t in zip(data_activity['N'], data_activity['Activity_Naiwny']) if t is not None]
t_naive_act = [t for t in data_activity['Activity_Naiwny'] if t is not None]

ax3.plot(n_naive_act, t_naive_act, marker='^', label='Naiwny', linestyle=':')
ax3.plot(data_activity['N'], data_activity['Activity_DP'], marker='o', label='Dynamiczny')
ax3.plot(data_activity['N'], data_activity['Activity_Iter'], marker='x', label='Iteracyjny)')
ax3.set_title('Wybór zajęć')
ax3.set_xlabel('N')
ax3.set_ylabel('Czas (us)')
ax3.set_yscale('log') 
ax3.legend()
ax3.grid(True, which="both", ls="-", alpha=0.5)
ax3.text(0.5, 0.9, 'Oś Y: Skala Logarytmiczna', transform=ax3.transAxes, ha='center', fontsize=9, bbox=dict(facecolor='white', alpha=0.8))


ax4 = axs[1, 1]

n_naive_rod = [n for n, t in zip(data_cutrod['N'], data_cutrod['CutRod_Naiwny']) if t is not None]
t_naive_rod = [t for t in data_cutrod['CutRod_Naiwny'] if t is not None]

ax4.plot(n_naive_rod, t_naive_rod, marker='^', color='red', label='Naiwny')
ax4.plot(data_cutrod['N'], data_cutrod['CutRod_Spam'], marker='o', label='Spamiętywanie')
ax4.plot(data_cutrod['N'], data_cutrod['CutRod_Iter'], marker='x', label='Iteracyjny')
ax4.set_title('Cięcie pręta')
ax4.set_xlabel('N')
ax4.set_ylabel('Czas (us)')
ax4.set_yscale('log') 
ax4.legend()
ax4.grid(True, which="both", ls="-", alpha=0.5)
ax4.text(0.5, 0.9, 'Oś Y: Skala Logarytmiczna ', transform=ax4.transAxes, ha='center', fontsize=9, bbox=dict(facecolor='white', alpha=0.8))

plt.tight_layout()
plt.show()