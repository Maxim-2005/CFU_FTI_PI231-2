def gcd(number):
    if len(number) != 10:
        return(print("Некоректный вводы"))
    else:
        try: 
            number = bin(int(number))
            if str(number)[-3::] == "000":
                return(print(8))
            elif str(number)[-2::] == "00":
                return(print(4))
            elif str(number)[-1::] == "0":
                return(print(2))
            else:
                return (print(1))
        except Exception as exc:
            return print(f"Некорректный ввод, ошибка: {exc}")
