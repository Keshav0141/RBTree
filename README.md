# 🌳 Red-Black Tree Implementation in C++

## 📌 Overview
This project is an implementation of a **Red-Black Tree (RBTree)** in C++.  
A Red-Black Tree is a **self-balancing binary search tree (BST)** that ensures insertion and deletion operations take **O(log n)** time.

This project demonstrates:
- **Insertion** with balancing (rotations + recoloring).
- **Deletion** with balancing.
- **Level-order traversal** (BFS).
- A **menu-driven CLI program** for easy interaction.

---

## 📖 What is a Red-Black Tree?
A **Red-Black Tree** is a binary search tree with extra properties that keep it balanced:

### ✅ Properties
1. Every node is either **Red** or **Black**.
2. The **root node is always Black**.
3. All **NULL (leaf) nodes are Black**.
4. If a node is **Red**, its children must be **Black** (no two consecutive Red nodes).
5. Every path from a node to its descendant NULL nodes has the **same number of Black nodes** (Black height).

These rules ensure the tree’s height is always close to `log₂(n)`, providing efficient operations.

---

## ⚙️ Features
- Insert nodes with **automatic balancing**.
- Delete nodes while maintaining tree properties.
- Print the tree in **level-order** with node colors.
- Simple **menu-driven interface**.

---
