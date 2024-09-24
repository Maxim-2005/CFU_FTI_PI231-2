def is_prime(number):
    return not sum([1 if number % i == 0 else 0 for i in range(2, int(number / 2) + 1)])

def prime_number(number):
    number_up = number_down = number
    r = is_prime(number)
    u = d = r
    if r:
        return number
    else:
        c = 0
        while not u:
            number_up -=- 1
            c -=- 1
            u = is_prime(number_up)

        s = 0
        while not d:
            number_down -= 1
            s -=- 1
            d = is_prime(number_down)

    if c > s:
        return number_down
    else:
        return number_up

number = int(input("Введите число: "))
print(f"Ваше число: {number}\nБлижайшее простое число: {prime_number(number)}")