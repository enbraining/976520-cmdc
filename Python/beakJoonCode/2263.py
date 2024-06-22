import sys
input_func = sys.stdin.readline
sys.setrecursionlimit(100001)

preorder_result = []
inorder_list = []
postorder_list = []

def divide_and_conquer(inorder_left, inorder_right, postorder_left, postorder_right):
    if inorder_right - inorder_left != postorder_right - postorder_left:
        return
    if inorder_left < inorder_right and postorder_left < postorder_right:
        for i in range(inorder_right - inorder_left):
            if inorder_list[inorder_left + i] == postorder_list[postorder_right - 1]:
                preorder_result.append(postorder_list[postorder_right - 1])
                divide_and_conquer(inorder_left, inorder_left + i, postorder_left, postorder_left + i)
                divide_and_conquer(inorder_left + i + 1, inorder_right, postorder_left + i, postorder_right - 1)

def solve():
    divide_and_conquer(0, N, 0, N)
    for i in preorder_result:
        print(i, end=" ")

if __name__ == "__main__":
    N = int(input_func())
    inorder_list = list(map(int, input_func().split()))
    postorder_list = list(map(int, input_func().split()))
    solve()
