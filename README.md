# Advent of Code 2024: RPG Challenge
This repository contains solutions for Advent of Code 2024, presented with a unique twist: an RPG-inspired system. 
In this approach, solving puzzles becomes part of a larger challenge involving resource management, constraints, and character progression.
Instead of solving puzzles straightforwardly, you manage a limited energy pool, contend with aging as you rest, and carefully use an artifact with specific rules and restrictions.


---

| Mon | Tue | Wed | Thu | Fri | Sat | Sun |
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|  |   |   |   |  |    | [Day 1](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room1/Room1.cpp) <br> ⭐⭐ <br> Age 20 |
| [Day 2](https://github.com/Sycix-HK/Advent-of-Code-2024-RPG/blob/main/Dungeon/Room2/Room2.cpp) <br> ⭐⭐ <br> Age 21 | Day 3 <br> ⏳⏳  | Day 4 <br> ⏳⏳  | Day 5 <br> ⏳⏳  | Day 6 <br> ⏳⏳  | Day 7 <br> ⏳⏳  | Day 8 <br> ⏳⏳  |
| Day 9 <br> ⏳⏳ | Day 10 <br> ⏳⏳  | Day 11 <br> ⏳⏳  | Day 12 <br> ⏳⏳  | Day 13 <br> ⏳⏳  | Day 14 <br> ⏳⏳  | Day 15 <br> ⏳⏳  |
| Day 16 <br> ⏳⏳ | Day 17 <br> ⏳⏳  | Day 18 <br> ⏳⏳  | Day 19 <br> ⏳⏳  | Day 20 <br> ⏳⏳  | Day 21 <br> ⏳⏳  | Day 22 <br> ⏳⏳  |
| Day 23 <br> ⏳⏳ |  Day 24 <br> ⏳⏳  |   Day 25 <br> ⏳⏳ |   |   |

---

![image](https://github.com/user-attachments/assets/0e9feb51-3cec-4640-bac4-3d26310f038a)


# Features and Rules

### Energy System
- Every memory allocation deducts from your energy pool.
- Some personal rules:
    - Loop indicies and const/cache variables do not have to cost energy, since you could obviously replace them by computing the same line everywhere it's used
 
### Artifact:
  - Creates a custom scope where allocations won't cost energy, but each line of use wears it down, introducing loss of characters to use inside scope next time.
  - You may only use the artifact once per enemy (aoc half day)
  - You may not use it inside loops
  - You may not return early from the artifact's scope
  - Every 10 lines used will break characters, constraining the letters you can use within the artifact's scope for consequent uses, until repaired.
  - You may not exceed 25 broken characters, not even if you intend to repair it after.
  - When dealing with a long line with multiple operations or lambda functions inside them (like an std::transform or std::acumulate), the rule is that each ; counts as a line. So an std::transform with a lambda function with a single return line costs 2 lines of wear.

### Resting and Aging:
  - Resting between puzzles restores energy but increases your character’s age.
  - You may also repair the artifact between puzzles, which won't restore energy, but will clear all broken characters from the artifact to give a fresh start to it. This action will age you the same way.
  - Your goal is to complete the challenges as young as possible.


