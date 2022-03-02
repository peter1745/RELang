import io;
import memory;

def MyGlobalInt : u32 = 5012;

def MyStorage -> storage
{
    def MyStorage(i : i32)
    {
        PublicInt = i;
    }

    pubdef PublicInt : i32;
    pubdef @PublicIntProp => PublicInt;
    pubdef @PublicIntProp
    {
        set => PublicInt = value * 50;
        get => PublicInt;
    }

    def PrivateInt : i32;
    def PrivateDouble : f64;
    def PrivateFloat : f32;
}

// Any parameter with a type ending in & will be passed as a mutable reference
def Add(i : u32&, j : u32&) -> int
{
    return i + j;
}

// Any parameter with a type ending with $ will be passed as a copy
def AddCopy(i : u32$, j : u32$) -> int
{
    return i + j;
}

// No -> type will be interpreted as returning void
def Entry()
{
    io::print("This is some string %d, Add(50, 10));

    def tmp : i32 = 0;
    io::readline("Enter a number: ", "%d", tmp);

    io::print("You entered: %d, tmp);

    def storage : MyStorage = MyStorage(50);
    storage.PublicInt = 100;
    storage.PublicIntProp = 10;
    storage.PrivateInt = 5; // Invalid

    def heapStorage : MyStorage* = memory::new(MyStorage);
    heapStorage->PublicInt = 50;

    // De-references heapStorage and passes PublicInt as a reference
    Add(*heapStorage.PublicInt, 10);
}
