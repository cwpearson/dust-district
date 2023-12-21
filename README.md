# dust-district

In the *Dust District* level of Dishonored 2, the player encounters a riddle like the following:

> At the dinner party were Lady Winslow, Doctor Marcolla, Countess Contee, Madam Natsiou, and Baroness Finch.
> 
> The women sat in a row. They all wore different colors and Countess Contee wore a jaunty purple hat. Madam Natsiou was at the far left, next to the guest wearing a blue jacket. The lady in green sat left of someone in red. I remember that green outfit because the woman spilled her beer all over it. The traveler from Dabokva was dressed entirely in white. When one of the dinner guests bragged about her War Medal, the woman next to her said they were finer in Dabokva, where she lived.
> 
> So Lady Winslow showed off a prized Ring, at which the lady from Baleton scoffed, saying it was no match for her Bird Pendant. Someone else carried a valuable Snuff Tin and when she saw it, the visitor from Fraeport next to her almost spilled her neighbor's absinthe. Baroness Finch raised her wine in toast. The lady from Karnaca, full of rum, jumped up onto the table, falling onto the guest in the center seat, spilling the poor woman's whiskey. Then Doctor Marcolla captivated them all with a story about her wild youth in Dunwall.
>
> In the morning, there were four heirlooms under the table: the War Medal, Diamond, the Bird Pendant, and the Snuff Tin.
> 
> But who owned each?

This repository has two c++ programs to solve the riddle: `bf.cpp` to solve it through a brute-force search, and `dfs.cpp` to solve it through a depth-first search.

```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make && ./bf
```

`bf` prints output like this:
```
 1 2 3 4 5 6 7 8 9 10 11 12 13
== PERMUTATION 1315376933 ==
  NATSIOU    FINCH   CONTEE MARCOLLA  WINSLOW
      TIN    MEDAL  PENDANT  DIAMOND     RING
  DABOKVA FRAEPORT  BALETON  DUNWALL  KARNACA
 ABSINTHE     WINE  WHISKEY     BEER      RUM
    WHITE     BLUE   PURPLE    GREEN      RED
```

Each column is a position, from left-to-right, featuring the woman, her item, her city, her drink, and her color.

`dfs` prints output like this
```
SUCCESS! (checked 5356 arrangements, exluded 3490 subtrees)
  NATSIOU    FINCH   CONTEE MARCOLLA  WINSLOW
      TIN    MEDAL  PENDANT  DIAMOND     RING
  DABOKVA FRAEPORT  BALETON  DUNWALL  KARNACA
 ABSINTHE     WINE  WHISKEY     BEER      RUM
    WHITE     BLUE   PURPLE    GREEN      RED
DONE (checked 16783 arrangements, exluded 10941 subtrees)
```
