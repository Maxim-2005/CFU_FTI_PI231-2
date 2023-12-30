class Hack {
public:
    int hack_trash, hack_secret;
};

// создание класса являющегося полным клоном, только с публичным 
// доступом и через его интерфейс реализуем обьект
int& hack_it(Keeper& keeper) {
    return ((Hack*)(&keeper))->hack_secret;
};
