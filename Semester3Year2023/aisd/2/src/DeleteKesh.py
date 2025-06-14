import os

# specify the directory paths where the temporary files are located
directory_paths = [
    "results", 
    "png"
]

# loop through all the files in the directories and delete them
for directory_path in directory_paths:
    folders = os.listdir(directory_path)
    for folder in folders:
        files = os.listdir(directory_path + "/" + folder)
        for file in files:
            os.remove(directory_path + "/" + folder + "/" + file)

