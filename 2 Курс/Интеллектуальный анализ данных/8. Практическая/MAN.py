def classify_with_if(attributes):  
    # Проверяем уровень "Senior"
    if attributes['level'] == 'Senior':  
        # Если язык "Java"
        if attributes['lang'] == 'Java':  
            # Если твитов нет
            if attributes['tweets'] == 'no':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return False  # Классификация: False
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return False  # Классификация: False
                # Невалидное значение PhD
                else:  
                    return None  
            # Если твиты есть
            elif attributes['tweets'] == 'yes':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return True  # Классификация: True
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return None  # Условие для покрытия всех веток
                # Невалидное значение PhD
                else:  
                    return None  
            # Невалидное значение tweets
            else:  
                return None  
        # Если язык "Python"
        elif attributes['lang'] == 'Python':  
            # Если твитов нет
            if attributes['tweets'] == 'no':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return True  # Классификация: True
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return True  # Классификация: True
                # Невалидное значение PhD
                else:  
                    return None  
            # Если твиты есть
            elif attributes['tweets'] == 'yes':  
                # Если есть PhD
                if attributes['phd'] == 'yes':  
                    return True  # Классификация: True
                # Если нет PhD
                elif attributes['phd'] == 'no':  
                    return None  # Условие для покрытия всех веток
                # Невалидное значение PhD
                else:  
                    return None  
            # Невалидное значение tweets
            else:  
                return None  
        # Если язык "C++"
        elif attributes['lang'] == 'C++':  
            # Если твитов нет
            if attributes['tweets'] == 'no':  
                # Если есть PhD
                if attributes['phd'] == 'yes':  
                    return False  # Классификация: False
                # Если нет PhD
                elif attributes['phd'] == 'no':  
                    return None  # Дополнительная ветвь для покрытия всех случаев
                # Невалидное значение PhD
                else:  
                    return None  
            # Если твиты есть
            elif attributes['tweets'] == 'yes':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return False  # Классификация: False
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return None  # Условие для покрытия всех веток
                # Невалидное значение PhD
                else:  
                    return None  
            # Невалидное значение tweets
            else:  
                return None  
        # Невалидное значение языка
        else:  
            return None  

    # Если уровень "Mid"
    elif attributes['level'] == 'Mid':  
        # Если язык "Python"
        if attributes['lang'] == 'Python':  
            # Если твитов нет
            if attributes['tweets'] == 'no':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return True  # Классификация: True
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return True  # Классификация: True
                # Невалидное значение PhD
                else:  
                    return None  
            # Если твиты есть
            elif attributes['tweets'] == 'yes':  
                # Если есть PhD
                if attributes['phd'] == 'yes':  
                    return True  # Классификация: True
                # Если нет PhD
                elif attributes['phd'] == 'no':  
                    return None  # Условие для покрытия всех веток
                # Невалидное значение PhD
                else:  
                    return None  
            # Невалидное значение tweets
            else:  
                return None  
        # Если язык "Java"
        elif attributes['lang'] == 'Java':  
            # Если твитов нет
            if attributes['tweets'] == 'no':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return False  # Классификация: False
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return False  # Классификация: False
                # Невалидное значение PhD
                else:  
                    return None  
            # Если твиты есть
            elif attributes['tweets'] == 'yes':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return False  # Классификация: False
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return None  # Условие для покрытия всех веток
                # Невалидное значение PhD
                else:  
                    return None  
            # Невалидное значение tweets
            else:  
                return None  
        # Невалидное значение языка
        else:  
            return None  
    # Если уровень "Junior"
    elif attributes['level'] == 'Junior':  
        # Если язык "Python"
        if attributes['lang'] == 'Python':  
            # Если твитов нет
            if attributes['tweets'] == 'no':  
                # Если нет PhD
                if attributes['phd'] == 'no':  
                    return True  # Классификация: True
                # Если есть PhD
                elif attributes['phd'] == 'yes':  
                    return False  # Классификация: False
                # Невалидное значение PhD
                else:  
                    return None  
            # Если твиты есть
            elif attributes['tweets'] == 'yes':  
                # Если есть PhD
                if attributes['phd'] == 'yes':  
                    return False  # Классификация: False
                # Если нет PhD
                elif attributes['phd'] == 'no':  
                    return None  # Условие для покрытия всех веток
                # Невалидное значение PhD
                else:  
                    return None  
            # Невалидное значение tweets
            else:  
                return None  
        # Невалидное значение языка
        else:  
            return None  
    # Уровень не распознан
    else:  
        return None  

# Пример использования
attributes = {'level': 'Senior', 'lang': 'Java', 'tweets': 'no', 'phd': 'no'}  
print(classify_with_if(attributes))  # Вывод результата классификации