def get_counter():
    x = 0
    def inner():
        nonlocal x
        x += 1
        return x
    return inner

counter = get_counter()
print(counter(), counter())