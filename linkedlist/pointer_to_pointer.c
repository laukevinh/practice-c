/* See push.c for code. Below is one explanation
   of pointer to pointer and how they're used
   to implement push for linkedlists.

##############################################
########### 1st call push(NULL, 1) ###########
##############################################

in main()

+------ head ------+
|     |            |
| 0xA |    NULL    |
|     |            |
+------------------+

in push()

+---- head_ref ----+    head_ref is pointer
|     |            |    to head, i.e. pointer
| 0xF |    0xA     |    to pointer.
|     |            |
+------------------+

+---- newnode -----+    newnode is pointer to
|     |            |    address of allocated
| 0xD |    0x1     |    memory
|     |            |
+------------------+

+------------------+
|     |   |        |
| 0x1 | ? |  ????  |
|     |   |        |
+------------------+

+------------------+    newnode->next refers
|     |   |        |    to head, i.e.
| 0x1 | 1 |  NULL  |    *head_ref
|     |   |        |
+------------------+

+------ head ------+    dereference head_ref
|     |            |    to change head value
| 0xA |    0x1     |    *head_ref = &newnode
|     |            |
+------------------+

##############################################
########### 2nd call push(head, 2) ###########
##############################################

in main()

+------ head ------+
|     |            |
| 0xA |    0x1     |
|     |            |
+------------------+

+------------------+    head points to node 
|     |   |        |
| 0x1 | 1 |  NULL  |
|     |   |        |
+------------------+

in push()

+---- head_ref ----+    new head_ref at 0xE
|     |            |
| 0xE |    0xA     |
|     |            |
+------------------+

+---- newnode -----+    newnode is pointer to
|     |            |    address of allocated
| 0xC |    0x2     |    memory
|     |            |
+------------------+

+------------------+    +------------------+
|     |   |        |    |     |   |        |
| 0x2 | 2 |  0x1 ------>| 0x1 | 1 |  NULL  |
|     |   |        |    |     |   |        |
+------------------+    +------------------+

+------ head ------+    dereference head_ref
|     |            |    to change head value
| 0xA |    0x2     |    *head_ref = &newnode
|     |            |
+------------------+

*/
