# Imports
import pandas as pd
import matplotlib.pyplot as plt

# Load the data
data = pd.read_csv('output_01.csv')

# Function to clean specific columns
def clean_column(column, prefix):
    return column.str.replace(prefix, '').astype('Int64')

# Clean relevant columns
data['pkt'] = clean_column(data['pkt'], 'pkt_number: ')
data['ax'] = clean_column(data['ax'], 'Ax: ')
data['ay'] = clean_column(data['ay'], 'Ay: ')
data['az'] = clean_column(data['az'], 'Az: ')
data['gx'] = clean_column(data['gx'], 'Gx: ')
data['gy'] = clean_column(data['gy'], 'Gy: ')
data['gz'] = clean_column(data['gz'], 'Gz: ')
data['id'] = data['id'].str.replace('ID: ', '').astype(int)

# Sorting the data by id and pkt to ensure correct differences
data = data.sort_values(by=['id', 'pkt'])

# Calculate the difference between the current row's gx, gy, gz and the previous row's gx, gy, gz
#data['gx_diff'] = data['gx'] - data['gx'].shift(1)
#data['gy_diff'] = data['gy'] - data['gy'].shift(1)
#data['gz_diff'] = data['gz'] - data['gz'].shift(1)

# Handling the first row's difference which will be NaN after the shift
data.loc[data.index[0], 'gx_diff'] = 0
data.loc[data.index[0], 'gy_diff'] = 0
data.loc[data.index[0], 'gz_diff'] = 0

# Create plots for each unique id
unique_ids = data['id'].unique()

for unique_id in unique_ids:
    df_id = data[data['id'] == unique_id]

    # Save file for each unique id as a CSV
    df_id.to_csv(f'possibly_decent_{unique_id}.csv', index=False)
    
    plt.figure(figsize=(12, 8))
    plt.plot(df_id['pkt'], df_id['ax'], label='ax')
    plt.plot(df_id['pkt'], df_id['ay'], label='ay')
    plt.plot(df_id['pkt'], df_id['az'], label='az')
    plt.plot(df_id['pkt'], df_id['gx'], label='gx')
    plt.plot(df_id['pkt'], df_id['gy'], label='gy')
    plt.plot(df_id['pkt'], df_id['gz'], label='gz')

    plt.xlabel('pkt')
    plt.ylabel('Value')
    plt.title(f'Sensor Data Over Packets for ID {unique_id}')
    plt.legend()
    plt.grid(True)

    # Save the graph as an image
    plt.savefig(f'sensor_data_plot_id_{unique_id}.png')

    # Show the plot
    plt.show()
