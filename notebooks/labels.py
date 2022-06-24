
def get_labels():
    infile = open("data.csv", 'r')
    outfile = open("data_with_labels.csv", 'w')

    outfile.write(infile.readline())

    for rawLine in infile:
        line = rawLine.split(',')[:-1]
        print("\n" + line[0])
        print("time: ", end='')
        label = input()
        outfile.write(rawLine[:-1] + label + "\n")

if __name__ == '__main__':
    get_labels()
