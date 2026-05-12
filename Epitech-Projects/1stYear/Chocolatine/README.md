# Chocolatine

**Chocolatine** is a GitHub Actions workflow project designed to improve your development workflow by enforcing integration and testing best practices. Just like the delicious pastry it’s named after, it helps you get through your day (and projects) more efficiently.

This project requires creating a reusable GitHub Actions workflow to automate checks such as coding style, compilation, testing, and repository mirroring.

## Project Goal

Create a GitHub Actions workflow named `chocolatine.yml` that can be reused across different Epitech projects.

The workflow must:

- Be fully self-contained (no external files required).
- Run only the allowed external actions.
- Avoid hardcoded sensitive data (use **secrets**).
- Run on each **push** and **pull request**, **except**:
  - If the branch name starts with `ga-ignore-`.
  - If the repository is the same as the mirror target.

## Setup

Place the `chocolatine.yml` file either:

- At the **root** of the repository, or
- In the `.github/workflows/` directory

### Environment Variables (workflow-level)

Define these variables at the top of your workflow file:

```yaml
env:
  MIRROR_URL: git@github.com:your-org/mirror-repo.git
  EXECUTABLES: "bin/my_program,tools/helper"
```
- `MIRROR_URL`: SSH URL of the mirror repo

- `EXECUTABLES`: Comma-separated list of expected compiled binaries

## Secrets

Use secrets to store sensitive data. Required:

- `GIT_SSH_PRIVATE_KEY`: SSH private key used for mirroring

## Workflow Overview
### Trigger Conditions

**The workflow must run on**:

- `push`

- `pull_request`

**But not when**:

- The branch starts with `ga-ignore-`

- The repo is the same as the `MIRROR_URL` target

## Jobs
1. **check_coding_style**

- Uses: `ghcr.io/epitech/coding-style-checker:latest`

- Steps:

    - `check.sh $(pwd) $(pwd)`

    - Display all errors as annotations

    - Fails if any errors are detected

1. **check_program_compilation**

- Uses: `epitechcontent/epitest-docker`

- Steps:

    - Run `make` with a 2-minute timeout

    - Run `make clean`

    - Check all files listed in `EXECUTABLES`:

        - Must exist and be executable

        - Fail with annotation if missing

2. **run_tests**

- Uses: `epitechcontent/epitest-docker`

- Step:

    - Run `make tests_run` (2 minute timeout)

3. **push_to_mirror**

- Uses: `pixta-dev/repository-mirroring-action`

- Condition: **only on push**

- Uses the `GIT_SSH_PRIVATE_KEY` secret to authenticate

## Author
- [@yohandprt](https://github.com/yohandprt)