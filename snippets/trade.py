from datetime import datetime
from datetime import timedelta

res_exchange = {}


def get_max_count(trades):
    i = 0
    count = 1
    while i + count < len(trades):
        start = trades[i]
        end = start + timedelta(minutes=1)
        while i + count < len(trades) and trades[i + count] < end:
            count += 1
        i += 1
    return count


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
    for e, timestamps in table:
        print(get_max_count(timestamps))


main()
