#ifndef LAB3_NODE_H
#define LAB3_NODE_H

struct Node
{
   int page;
   int lastUsedAt;
   int index;
   int count = 0;
   float faultRate = 0.0;
   int arrivalTime = 0;
   Node *next;
};

#endif //LAB3_NODE_H
