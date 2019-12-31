def split_test():
    file_content = open("./Watcher.txt").readlines()
    file_content = "".join(file_content)
    tokens = file_content.split()
    print(len(tokens), " ",  tokens[100], " ", tokens[200])
