using System.Collections.Generic;
using System;

class Stack
{
    // Lists are like really powerful arrays in C# that can change size easily.
    // They have a lot of built-in methods that make it easy to add, remove, and
    // read things, making a stack actually super simple.
    private List<int> items;

    // Stack constructor inits the list
    public Stack()
    {
        items = new List<int>();
    }

    // push uses List Add method to add an int at the end
    public void Push(int item)
    {
        items.Add(item);
    }

    // Pop gets the last item, then removes it and returns the item.
    public int Pop()
    {
        if (IsEmpty())
        {
            throw new InvalidOperationException("Stack is empty");
        }

        int item = items[items.Count - 1];
        items.RemoveAt(items.Count - 1);
        return item;
    }

    // Peak just returns the last item without removing it.
    public int Peek()
    {
        if (IsEmpty())
        {
            throw new InvalidOperationException("Stack is empty");
        }
        return items[items.Count - 1];
    }

    // IsEmpty checks if the list has no items, so we can throw errors if the stack is empty
    public bool IsEmpty()
    {
        return items.Count == 0;
    }

    // Size just returns how many items are in the list, which is the size of the stack.
    public int Size()
    {
        return items.Count;
    }
}

class Program
{
    static void Main()
    {
        Console.WriteLine("Basic Test:");
        Console.WriteLine();
        Stack stack = new Stack();
        stack.Push(10);
        stack.Push(20);
        stack.Push(30);
        Console.WriteLine("Pushed 10, 20, 30");
        Console.WriteLine("Size: " + stack.Size());
        Console.WriteLine("Peek: " + stack.Peek());
        Console.WriteLine("Pop: " + stack.Pop());
        Console.WriteLine("Size after pop: " + stack.Size());
        Console.WriteLine("IsEmpty: " + stack.IsEmpty());
        Console.WriteLine();

        Console.WriteLine("Big Test:");
        Console.WriteLine();

        Stack bigStack = new Stack();
        int testSize = 1000;
        
        for (int i = 1; i <= testSize; i++)
        {
            bigStack.Push(i);
        }
        Console.WriteLine("Pushed " + testSize + " elements");
        Console.WriteLine("Size: " + bigStack.Size());
        
        for (int i = 0; i < testSize / 2; i++)
        {
            bigStack.Pop();
        }
        Console.WriteLine("After popping 500 elements:");
        Console.WriteLine("Size: " + bigStack.Size());

        // Pop remaining
        for (int i = 0; i < testSize / 2; i++)
        {
            bigStack.Pop();
        }
        Console.WriteLine("After popping remaining 500:");
        Console.WriteLine("IsEmpty: " + bigStack.IsEmpty());
    }
}
