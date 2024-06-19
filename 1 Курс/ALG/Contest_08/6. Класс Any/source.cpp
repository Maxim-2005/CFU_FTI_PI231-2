// Реализация конструкторов
Any::Any(int* data) : data(data), type(Type::INT) {};
Any::Any(double* data) : data(data), type(Type::DOUBLE) {};
Any::Any(std::string* data) : data(data), type(Type::STRING) {};
Any::Any(std::vector<Any*>* data) : data(data), type(Type::VECTOR_ANY_PTR) {};

// Реализация деструктора
Any::~Any() {
    if (type == Type::VECTOR_ANY_PTR) {
        std::vector<Any*>* v = static_cast<std::vector<Any*>*>(data);
        for (auto e : *v)
            delete e;
        delete v;
    } else
        delete data;
};

// Реализация операторов:

Any::operator int() {
    if (type != Type::INT)
        throw "";
    return *(int*)data;
};

Any::operator double() {
    if (type != Type::DOUBLE)
        throw "";
    return *(double*)data;
};

Any::operator std::string() {
    if (type != Type::STRING)
        throw "";
    return *(std::string*)data;
};

Any::operator std::vector<Any*>* () {
    if (type != Type::VECTOR_ANY_PTR)
        throw "";
    return static_cast<std::vector<Any*>*>(data);
};

std::ostream& operator<<(std::ostream& out, const Any& val) {
    switch (val.type) {
        case Any::Type::INT:
            out << *static_cast<int*>(val.data);
            break;
        case Any::Type::DOUBLE:
            out << *static_cast<double*>(val.data);
            break;
        case Any::Type::STRING:
            out << *static_cast<std::string*>(val.data);
            break;
        case Any::Type::VECTOR_ANY_PTR:
            for (const Any* item : *static_cast<std::vector<Any*>*>(val.data)) {
                if (item != static_cast<std::vector<Any*>*>(val.data)->front())
                    out << " ";
                out << *item;
            }
            break;
    }

    return out;
};