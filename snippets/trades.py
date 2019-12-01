from datetime import datetime
from datetime import timedelta

res_exchange = {}


def get_max_count2(trades):
    i = 0
    windows_size = 1
    while i + windows_size < len(trades):
        start = trades[i]
        end = start + timedelta(minutes=1)
        while i + windows_size < len(trades) and trades[i + windows_size] < end:
            windows_size += 1
        i += 1
    return windows_size


def get_max_count(timestamps):
    res = 1
    i = 0
    start = timestamps[i]
    end = timestamps[i]
    while True:
        start = end
        end = timestamps[i+1] + timedelta(minutes=1)


        pass
    return res


def make_table(lines):
    table = {}
    for line in lines:
        line = line.strip()
        time, price, size, exchange = line.split(',')
        time = datetime.strptime(time, '%H:%M:%S.%f')
        if exchange in table:
            table[exchange].append(time)
        else:
            table[exchange] = [time]
    return sorted(table.items())


def read_file(filename):
    with open(filename, 'r') as file:
        return file.readlines()


def main():
    table = make_table(read_file('trades.csv'))
    for e,timestamps in table:
        print(get_max_count(timestamps))


main()