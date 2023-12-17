// Ваш код здесь
class OSUpdater : public IRunnable {
    //в качестве действия выводят на экран имя класса
    void run() override {
        std::cout << "OSUpdater" << std::endl;
    };
};

class Alarm : public IRunnable {
public:
    //в качестве действия выводят на экран имя класса
    void run() override {
        std::cout << "Alarm" << std::endl;
    };
};

class ActivityChecker : public IRunnable {
public:
    //в качестве действия выводят на экран имя класса
    void run() override {
        std::cout << "ActivityChecker" << std::endl;
    };
};

#include <vector>
#include <iomanip>

class Clock : public IRunnable, public IClock {
public:
    //Список событий
    std::vector<std::pair<IRunnable*, Time>> events;

    //в качестве действия вызывает у себя next, пока не закончатся все события которые были установлены ранее.
    void run() override {
        while (next());
    };

    //"запоминает" событие (объект реализующий интерфейс IRunnable) и временную метку;
    void add(IRunnable* client, Time time) override {
        events.push_back(std::make_pair(client, time));
    };

    //выполняет запуск следующего по времени события и удаляет его из списка. Перед запуском события
    //выводится временная метка в формате часы:минуты:секунды. Если событий нет, то возвращает false.
    bool next() override {
        if (events.empty())
            return false;

        auto it = events.begin();
        auto nextEvent = it;
        for (; it != events.end(); ++it) {
            if (it->second < nextEvent->second)
                nextEvent = it;
        }

        std::cout
            << std::setfill('0') << std::setw(2) << nextEvent->second.hours << ":"
            << std::setfill('0') << std::setw(2) << nextEvent->second.minutes << ":"
            << std::setfill('0') << std::setw(2) << nextEvent->second.seconds << " ";

        nextEvent->first->run();
        events.erase(nextEvent);

        return true;
    };
};