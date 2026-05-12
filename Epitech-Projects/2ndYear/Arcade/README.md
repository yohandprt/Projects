# Arcade

## Compilation

```bash
make              # compile l'entièretée du projet
make core         # compile seulement l'éxécutable principal
make graphicals   # compile seulement les bibliothèques graphiques
make games        # compile seulement les jeux
```

## Lancement

```bash
./arcade <chemin_vers_lib_graphique_au_choix> # Lance le projet et affiche le menu sur la librairie graphique demandé
```

## Touches

- **TAB** : Changer de bibliothèque graphique
- **SPACE** : Changer de jeu
- **R** : Reset le jeu actuel
- **M** : Retour au menu
- **ESC** : Quitter

## Architecture

- **Modules graphiques** : SFML (`./lib/arcade_sfml.so`), SDL2 (`./lib/arcade_sdl2.so`), NCURSES (`./lib/arcade_ncurses.so`)
- **Jeux** : Pac-Man (`./lib/arcade_pacman.so`) , Snake (`./lib/arcade_snake.so`)

### Classe des interfaces graphique

```cpp
class IDisplayModule : public IModule {
    virtual void init() = 0;
    virtual void stop() = 0;
    virtual bool isOpen() = 0;
    virtual bool pollEvent() = 0;
    virtual void close() = 0;
    virtual void clear() = 0;
    virtual void display() = 0;
};
```

### Classe des interfaces des jeux

```cpp
class IGameModule : public IModule {
    virtual void init(unique_ptr<ADisplayModule>&, GameState&) = 0;
    virtual void stop() = 0;
    virtual void handleKeys(unique_ptr<ADisplayModule>&, GameState&) = 0;
    virtual void update(GameState&) = 0;
    virtual bool isRunning() const = 0;
};
```