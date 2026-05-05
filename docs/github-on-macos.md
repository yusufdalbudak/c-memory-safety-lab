# GitHub on macOS for Cybersecurity Projects

This document explains how to set up GitHub on macOS and share cybersecurity-focused C projects responsibly.

## 1. Install Git
Install Apple command line tools if needed:
```sh
xcode-select --install
```

## 2. Configure Git
Set your identity:
```sh
git config --global user.name "Your Name"
git config --global user.email "your_email@example.com"
git config --global init.defaultBranch main
```

## 3. Generate SSH keys
Create and add an SSH key for GitHub:
```sh
ssh-keygen -t ed25519 -C "your_email@example.com"
cat ~/.ssh/id_ed25519.pub
```
Then copy the public key into GitHub settings.

## 4. Initialize a repository
From a project directory:
```sh
git init
printf "*.o\nbuild/\n" > .gitignore
git add .
git commit -m "Initial commit"
```

## 5. Connect to GitHub and push
```shngit remote add origin git@github.com:username/repo.git
git push -u origin main
```

## 6. Best practices for cybersecurity projects
- Document the project clearly in `README.md`
- Add `SECURITY.md` for security notes and disclaimers
- Never commit credentials, API keys, or private data
- Label vulnerable examples explicitly in filenames and comments
- Use a license and state the intended use case clearly
- Keep code modular, and separate unsafe examples from secure implementations

## 7. macOS-specific tips
- Use `clang` and `strlcpy`/`strlcat` to build safe string handling
- Use `brew install openssl` only when you need crypto libraries and avoid homegrown crypto
- Verify `ssh-agent` is running before pushing:
```sh
eval "$(ssh-agent -s)"
ssh-add --apple-use-keychain ~/.ssh/id_ed25519
```
