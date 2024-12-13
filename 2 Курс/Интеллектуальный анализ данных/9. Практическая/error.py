from dsmltf import KMeans, squared_distance

def squared_errors(inps, k):
    clasterbuilder = KMeans(k)
    clasterbuilder.train(inps)
    means = clasterbuilder.means
    inclaster = map(clasterbuilder.classify, inps)
    return sum(squared_distance(inp, means[cluster]) for inp, cluster in zip(inps, inclaster))
