from dsmltf import build_tree_id3, classify


inputs_1 = [
    ({'level': 'Senior', 'lang': 'Java', 'tweets': 'no', 'phd': 'no'}, False),
    ({'level': 'Senior', 'lang': 'Java', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Mid', 'lang': 'Python', 'tweets': 'no', 'phd': 'no'}, True),
    ({'level': 'Junior', 'lang': 'Python', 'tweets': 'no', 'phd': 'no'}, True),
    ({'level': 'Junior', 'lang': 'Python', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Senior', 'lang': 'Python', 'tweets': 'yes', 'phd': 'yes'}, True),
    ({'level': 'Mid', 'lang': 'Java', 'tweets': 'yes', 'phd': 'no'}, False),
    ({'level': 'Mid', 'lang': 'C++', 'tweets': 'no', 'phd': 'yes'}, True),
    ({'level': 'Junior', 'lang': 'C++', 'tweets': 'yes', 'phd': 'no'}, False),
    ({'level': 'Senior', 'lang': 'Go', 'tweets': 'yes', 'phd': 'no'}, True),
    ({'level': 'Junior', 'lang': 'Java', 'tweets': 'no', 'phd': 'no'}, True),
    ({'level': 'Mid', 'lang': 'Go', 'tweets': 'no', 'phd': 'yes'}, True),
    ({'level': 'Senior', 'lang': 'Python', 'tweets': 'no', 'phd': 'no'}, True),
    ({'level': 'Junior', 'lang': 'Go', 'tweets': 'yes', 'phd': 'yes'}, False),
    ({'level': 'Mid', 'lang': 'Java', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Senior', 'lang': 'C++', 'tweets': 'yes', 'phd': 'no'}, False),
    ({'level': 'Junior', 'lang': 'C++', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Mid', 'lang': 'Python', 'tweets': 'yes', 'phd': 'yes'}, True),
    ({'level': 'Senior', 'lang': 'JavaScript', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Mid', 'lang': 'JavaScript', 'tweets': 'yes', 'phd': 'no'}, True),
    ({'level': 'Junior', 'lang': 'JavaScript', 'tweets': 'yes', 'phd': 'no'}, True),
    ({'level': 'Senior', 'lang': 'Ruby', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Mid', 'lang': 'Ruby', 'tweets': 'no', 'phd': 'yes'}, True),
    ({'level': 'Junior', 'lang': 'Ruby', 'tweets': 'yes', 'phd': 'no'}, True),
    ({'level': 'Senior', 'lang': 'Go', 'tweets': 'no', 'phd': 'yes'}, True),
    ({'level': 'Mid', 'lang': 'Go', 'tweets': 'yes', 'phd': 'no'}, True),
    ({'level': 'Junior', 'lang': 'Go', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Senior', 'lang': 'PHP', 'tweets': 'yes', 'phd': 'no'}, False),
    ({'level': 'Mid', 'lang': 'PHP', 'tweets': 'no', 'phd': 'yes'}, True),
    ({'level': 'Junior', 'lang': 'PHP', 'tweets': 'yes', 'phd': 'no'}, False),
    ({'level': 'Senior', 'lang': 'Java', 'tweets': 'yes', 'phd': 'no'}, True),
    ({'level': 'Mid', 'lang': 'Java', 'tweets': 'no', 'phd': 'no'}, False),
    ({'level': 'Junior', 'lang': 'Java', 'tweets': 'yes', 'phd': 'yes'}, True),
    ({'level': 'Senior', 'lang': 'C++', 'tweets': 'no', 'phd': 'yes'}, False),
    ({'level': 'Mid', 'lang': 'C++', 'tweets': 'yes', 'phd': 'no'}, True),
]

tree = build_tree_id3(inputs_1)
print(classify(tree,{'level':'Senior', 'lang':'Java', 'tweets':'no', 'phd':'no'}))
