import pandas as pd
import numpy as np
from sklearn.preprocessing import StandardScaler

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

# Select the columns to be normalized and the columns to be left unchanged
columns_to_normalize = ['ax', 'ay', 'az', 'gx', 'gy', 'gz']
columns_to_leave = ['id', 'pkt']

# Normalize only the selected columns
scaler = StandardScaler()
data[columns_to_normalize] = scaler.fit_transform(data[columns_to_normalize])

# Select only the columns we are interested in after normalization
df = data[columns_to_leave + columns_to_normalize]

# Sorting the data
df = df.sort_values(by='id')
df = df.sort_values(by='pkt')


# Save the resulting DataFrame to a CSV file
df.to_csv('possibly_decent_111.csv', index=False)
