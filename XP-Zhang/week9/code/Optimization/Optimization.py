with open("data.txt", "r") as file:
    with open("out.txt","w") as f:
        for line in file:
            f.writelines(line.strip() + '& \\\\' + '\n' )
