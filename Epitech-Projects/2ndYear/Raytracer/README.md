# Raytracer

## Compilation

```bash
make # compile l'entièretée du projet
```

## Lancement

```bash
./raytracer <chemin_vers_le_fichier_de_config> # Lance le projet avec le fichier spécifié (fichier.cfg)
```

## Composants

- **Camera** - `origin`, `resolution`, `fov`, `bgColor`
_
- **Primitives**
    - **plane** - `axis`, `position`, `material`
    - **sphere** - `origin`, `rayon`, `material`
    - **cone** - `origin`, `rayon`, `height`, `rotation`, `scale`, `material`
    - **cylindre** - `origin`, `rayon`, `height`, `rotation`, `scale`, `material`
_
- **Lights**
    - **point** - `origin`, `color`
    - **directional** - `direction`, `color`
_
- **Materials** - `color`, `reflectivity`, `refractivity`, `transparency`
