def charfilter(string):
    arr = " "
    vowels = "aeiouyаеёиоуыэюя"
    bowels = "AEIOUYАЕЁИОУЫЭЮЯ"
    for i in string:
        if i in vowels or i in bowels:
            if arr[-1] != i:
                arr = arr + i
        else:
            arr += i
    arr = arr[1:]
    return print(arr)
        