def main():
    height = int(input("enter the arrow height: "))
    width = int(input("enter the arrow width: "))
    arrowHeadWidth = int(input("enter the arrow head width: "))

    # Arrow shaft
    for _ in range(height):
        print("*" * width)

    # Arrow head
    for i in range(arrowHeadWidth, 0, -1):
        print("*"  * (i))

if __name__ == "__main__":
    main()