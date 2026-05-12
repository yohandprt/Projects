## Comment implémenter de nouvelles librairies graphiques ?

### 1. Les classes principales

Tous les modules d'affichage doivent hériter de `ADisplayModule` et implémenter l'interface `IDisplayModule`.

**Interface IDisplayModule :**

```cpp
class IDisplayModule : public IModule {
public:
    virtual ~IDisplayModule() = default;
    virtual void init() = 0;              // Initialise les composants du jeu
    virtual void stop() = 0;              // Arrête le jeu
    virtual bool isOpen() = 0;            // Retourne vrai tant que la fenêtre est ouverte
    virtual bool pollEvent() = 0;         // Gère les événements
    virtual void close() = 0;             // Ferme la fenêtre
    virtual void clear() = 0;             // Nettoie la fenêtre pour ensuite y afficher la nouvelle image
    virtual void display() = 0;           // Affiche le rendu de l'image
};
```

**Abstraction de l'interface, ADisplayModule :**

```cpp
class ADisplayModule : public IDisplayModule {
public:
    virtual std::size_t getWindowSizeX() const = 0;              // Retourne la largeur de la fenêtre actuelle
    virtual std::size_t getWindowSizeY() const = 0;              // Retourne la hauteur de la fenêtre actuelle
    virtual bool isKeyPressed(std::string key) = 0;              // Vérifie si la touche spécifié est cliquée
    virtual std::unique_ptr<IRectangle> createRectangle() = 0;   // Crée un nouveau rectangle
    virtual std::unique_ptr<ICircle> createCircle() = 0;         // Crée un nouveau cercle
    virtual std::unique_ptr<IRectangle> createSprite() = 0;      // Crée un nouveau sprite
};
```

### 2. Création des composants du jeu
 
Chaque librairie graphique doit fournir des implémentations pour les rectangle, cercle et sprites :

**Exemple d'implémentation de Rectangle :**

```cpp
class NewRectangle : public ARCADE::IRectangle {
private:
    float _x;
    float _y;
    float _width;
    float _height;
    ARCADE::Color _color;
    std::string _text;
    ARCADE::Color _textColor;

public:
    NewRectangle() = default;

    void setPosition(float x, float y) override {_x = x; _y = y;}
    void setSize(float width, float height) override {_width = width; _height = height;}
    void setColor(ARCADE::Color color) override {_color = color;}
    void setText(const std::string& text) override {_text = text;}
    void setTextColor(ARCADE::Color color) override {_textColor = color;}

    float getX() const override {return _x;}
    float getY() const override {return _y;}
    float getWidth() const override {return _width;}
    float getHeight() const override {return _height;}
    ARCADE::Color getColor() const override {return _color;}
    std::string getText() const override {return _text;}
    ARCADE::Color getTextColor() const override {return _textColor;}

    void draw(std::unique_ptr<ARCADE::ADisplayModule>& display) override {
        // Code pour afficher le rectangle
    }
};
```

### 3. Classe graphique qui hérite de ADisplayModule

**Exemple d'implémentation de ADisplayModule (créer la base de la librairie graphique) :**

```cpp
#include "ADisplayModule.hpp"
#include "NewRectangle.hpp"
#include "NewCercle.hpp"
#include "NewSprite.hpp"

class NewGraphic : public ARCADE::ADisplayModule {

private:
    bool _isOpen;

public:
    MaLibGraphique() : _isOpen(false) {}

    void init() override {
        _isOpen = true;
    }

    void stop() override {
        _isOpen = false;
    }

    bool isOpen() override {
        return _isOpen;
    }

    bool pollEvent() override {
    }

    void close() override {
        _isOpen = false;
    }

    void clear() override {
    }

    void display() override {
    }

    std::size_t getWindowSizeX() const override {
        return 1920;
    }
    std::size_t getWindowSizeY() const override {
        return 1080;
    }

    bool isKeyPressed(std::string key) override {
    }

    std::unique_ptr<ARCADE::IRectangle> createRectangle() override {
        return std::make_unique<NewRectangle>();
    }

    std::unique_ptr<ARCADE::ICircle> createCircle() override {
        return std::make_unique<NewCercle>();
    }

    std::unique_ptr<ARCADE::IRectangle> createSprite() override {
        return std::make_unique<NewSprite>();
    }
};

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint()      // Création d'un entryPoint pour accéder à la librairie graphique dynamiquement
{
    return std::make_unique<NewGraphic>();
}
```

### 4. Bind des touches

Faire un `std::map` qui relie les touche de la lib graphique aux touches correspondantes :
- **Z**
- **Q**
- **S**
- **D**
- **M**
- **R**
- **UP**
- **DOWN**
- **LEFT**
- **RIGHT**
- **SPACE**
- **TAB**
- **ENTER**
- **ESC**

### 5. Compilation

**Exemple de Makefile :**

```makefile
SRC =   NewGraphic.cpp \
        NewRectangle.cpp \
        NewCercle.cpp \
        NewSprite.cpp

OBJ = $(SRC:.cpp=.o)

LIB_DIR = ./lib/

NAME = $(LIB_DIR)arcade_graphiclibname.so

CFLAGS = -fPIC -shared -I./include -std=c++20

$(NAME): $(OBJ)
    mkdir -p $(LIB_DIR)
    g++ $(OBJ) -o $(NAME) $(CFLAGS)
```

## Comment implémenter de nouvelles librairies de jeu ?

### 1. Les classes principales

Tous les jeux doivent hériter de `AGameModule` et implémenter l'interface `IGameModule`.

```cpp
class IGameModule : public IModule {
public:
    virtual void init(std::unique_ptr<ADisplayModule>& display, GameState& state) = 0;
    virtual void stop() = 0;
    virtual void handleKeys(std::unique_ptr<ADisplayModule>& display, GameState& state) = 0;
    virtual void update(GameState& state) = 0;
    virtual bool isRunning() const = 0;
};
```

### 2. Création du jeu

**Exemple d'implémentation de AGameModule (créer le fonctionnement du jeu) :**

```cpp
#include "AGameModule.hpp"
#include "GameState.hpp"

class NewGame : public ARCADE::AGameModule {

private:
    bool _running;

public:
    NewGame() : _running(false) {}

    void init(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override {
        _running = true;

        auto rect = display->createRectangle();        // On initialise un nouveau rectangle
        rect->setPosition(100, 100);
        rect->setSize(50, 50);
        rect->setColor(ARCADE::Color::Red);

        state.addShape("player", std::move(rect));     // On enregistre le rectangle pour pouvoir le sauvegarder
    }

    void stop() override {
        _running = false;
    }

    void handleKeys(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state) override { // Gestion des touches
        if (display->isKeyPressed("left")) {
            ...
        }
    }

    void update(ARCADE::GameState& state) override { // Met à jour le jeu (déplacement des ennemies, vérification des collisions, score, ...)
    }

    bool isRunning() const override {
        return _running;
    }
};

extern "C" std::unique_ptr<ARCADE::IModule> entryPoint() {      // Création d'un entryPoint pour accéder au jeu dynamiquement
    return std::make_unique<NewGame>();
}
```

### 3. Comment utiliser GameState pour sauvegarder le jeu ?

La classe `GameState` gère tous les objets dessinables :

```cpp
auto rect = display->createRectangle();           // On crée un composant

state.addShape("rect", std::unique_ptr<IShape>);   // On enregistre ce composant en lui donnant un nom (pour le trouver dans les autres formes)

std::unique_ptr<ARCADE::IShape>& shape = state.getShape("rect"); // On récupère la shape en IShape pour intéragir avec
std::unique_ptr<ARCADE::IRectangle>& rect = state.getShapeAs<ARCADE::IRectangle>("rect"); // (permet de récupèrer la shape directement au type voulu)

state.removeShape("rect"); // Destruction de la forme (ennemi tué, ...)
```

### 4. Compilation

**Exemple de Makefile :**

```makefile
SRC =   NewGame.cpp \

OBJ = $(SRC:.cpp=.o)

LIB_DIR = ./lib/

NAME = $(LIB_DIR)arcade_gamelibname.so

CFLAGS = -fPIC -shared -I./include -std=c++20

$(NAME): $(OBJ)
    mkdir -p $(LIB_DIR)
    g++ $(OBJ) -o $(NAME) $(CFLAGS)
```
