import pandas as pd
from nltk import pos_tag
from collections import defaultdict
from dsmltf import count_words, spam_probability, f1_score

# Вероятность нахождения слова в спаме
def word_probabilities(counts, total_spams, total_non_spams, k=0.5): 
    return [(w[0], (w[1] + k) / (total_spams + 2*k), 
            (w[2] + k) / (total_non_spams + 2*k) ) 
            for w in counts]

# Вывод F1 метрики
def test(words, dataset):
    true_pos, false_pos, false_neg = 0, 0, 0
    for i in dataset:
        match round(spam_probability(words, i[0])), i[1]:
            case 1, 1:
                true_pos += 1
            case 1, 0:
                false_pos += 1
            case 0, 1:
                false_neg += 1
    return f1_score(true_pos, false_pos, false_neg)

# Чтение dataset с кейгла
df = pd.read_csv('spam.csv', delimiter=',').values.tolist()
dataset = []
for row in df:
    dataset.append([row[1], 1 if row[0] == "spam" else 0])

# Колличество спам сообщений и хам сообщений
spam_count = len([i for i in dataset if i[1]])
ham_count = len(dataset) - spam_count

# Разделение на обучающую выборку
train_set = count_words(dataset[:-100]) # Все сообщение кроме последних 100
tagged_keys = pos_tag(train_set.keys()) # Ключи частей речи
train_set = defaultdict(lambda: [0, 0], 
    {key: train_set[key] for key, tag in tagged_keys if tag not in ('JJ', 'JJR', 'JJS')}) # Фильтр прилагательный

# Сортировка по длине слов
words = sorted(train_set, key=lambda x: train_set[x][0] if len(x) >= 5 else 0)[-7:] # Слова с длинной не меньше 5 букв
words = [(i, train_set[i][0] / spam_count,
    train_set[i][1] / ham_count if train_set[i][1] / ham_count else 0.01)  for i in words]

print("Без сглаживания: ", test(words, dataset[-100:]))

# Сглаживание
words_with_smoothing = word_probabilities([(i[0],
    train_set[i[0]][0], train_set[i[0]][1]) for i in words], spam_count, ham_count, k=0.5)

print("Со сглаживанием: ", test(words_with_smoothing, dataset[-100:]))