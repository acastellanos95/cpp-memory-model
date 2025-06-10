# Memory layout and alignment in C++

We want to see visually how memory is mapped. In `main.cpp` we provide 4 types of classes/structs and print their sizes.

```C++
Empty class size: 1
Class with methods class size: 1
Class with member fields class size: 24
Class with class member fields (static) class size: 24
```

Empty classes have a size of 1 byte because if used in arrays, there needs to be different adressess.
Using GDB we can see that for the empty class object:
```
p &empty[0]
$6 = (Empty *) 0x7fffffffd675
gef➤  p &empty[1]
$7 = (Empty *) 0x7fffffffd676
gef➤  p &empty[2]
$8 = (Empty *) 0x7fffffffd677
```

In the class with only one method is an empty struct:

```
gef➤  p &onlyMethods 
$2 = (OnlyMethods *) 0x7fffffffd650
```

For the Fields class, we know its size is 24:

```
gef➤  p fields
$7 = {
  a = 0x84d0,
  b = 0x1,
  c = 6.4398759999999999,
  d = 0x68
}
gef➤  x/24xb &fields
0x7fffffffd630:	0xd0	0x84	0x00	0x00	0x01	0x7f	0x00	0x00
0x7fffffffd638:	0x62	0x2e	0xa9	0xda	0x6e	0xc2	0x19	0x40
0x7fffffffd640:	0x68	0x00	0x00	0x00	0x00	0x00	0x00	0x00
```


