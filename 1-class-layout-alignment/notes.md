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

## Alignment

The alignment is a number power of 2, this are the size of succesive address or adressess at which objects can be
allocated. For example for the `fields` object, we now from the output of the code that its size is 24 and its alignment
is 8 bytes. Let's use the last memory watch of the `fields` object. Of course don't forget endianness, which in my case
is little-endian for an x64 Linux machine:

```C++
// Fields has size 24 bytes, and 8 bytes alignment.
struct Fields {
    int a; // For my architecture int has size 4 bytes and alignment of 4 bytes because is a fundamental type.
    bool b; // size: 1 byte, alignment: 1 byte.
    double c; // size: 8 bytes, alignment 8 bytes.
    char d; // size: 1 byte, alignment: 1 byte
};
```
The largest type is double with 8 bytes of size and alignment. This means we need the other to add some kind of padding
to all other types smaller than double. The compiler would optimize it adding 3 bytes padding to `b` and `d`:

```C++
struct Fields {
    int a; // For my architecture int has size 4 bytes and alignment of 4 bytes because is a fundamental type.
    bool b; // size: 1 byte, alignment: 1 byte.
    char bPadding[3];
    double c; // size: 8 bytes, alignment 8 bytes.
    char d; // size: 1 byte, alignment: 1 byte
    char dPadding[7];
};
```

So now it makes sense what the memory shows:

```
               | ------------ a ------------|  |  b |   | ---- bPadding --- |
0x7fffffffd630:	0xd0	0x84	0x00	0x00	0x01	0x7f	0x00	0x00
+ 8 bytes =    | --------------------------- c ---------------------------- |
0x7fffffffd638:	0x62	0x2e	0xa9	0xda	0x6e	0xc2	0x19	0x40
+ 8 bytes      |  d |   | -------------------- dPadding ------------------- |
0x7fffffffd640:	0x68	0x00	0x00	0x00	0x00	0x00	0x00	0x00
```
