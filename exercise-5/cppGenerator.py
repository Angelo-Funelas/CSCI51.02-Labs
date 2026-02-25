while (True):
    line = input()
    split_line = line.split("61")
    if (len(split_line) > 1):
        print(f"cout << \"{split_line[0]}\" << num << \"{split_line[1]}\\n\";")
    else:
        print(f"cout << \"{split_line[0]}\\n\";")