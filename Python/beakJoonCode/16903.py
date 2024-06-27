import sys
input = sys.stdin.readline

class TrieNode(object):
    def __init__(self, data):
        self.data = data
        self.left_child = {}
        self.right_child = {}

class BinaryTrie(object):
    def __init__(self):
        self.root = TrieNode(0)

    def insert_word(self, binary_word):
        current_node = self.root

        for binary_character in binary_word:
            if binary_character == "0":
                if current_node.left_child:
                    current_node.left_child.data += 1
                else:
                    current_node.left_child = TrieNode(0)
                current_node = current_node.left_child
            else:
                if current_node.right_child:
                    current_node.right_child.data += 1
                else:
                    current_node.right_child = TrieNode(0)
                current_node = current_node.right_child

    def delete_word(self, binary_word):
        current_node = self.root
        for binary_character in binary_word:
            if binary_character == "0":
                if current_node.left_child.data > 0:
                    current_node.left_child.data -= 1
                else:
                    current_node.left_child = False
                    break
                current_node = current_node.left_child
            else:
                if current_node.right_child.data > 0:
                    current_node.right_child.data -= 1
                else:
                    current_node.right_child = False
                    break
                current_node = current_node.right_child

    def find_maximum_xor(self, binary_word):
        current_node = self.root
        xor_result = "0b"

        for binary_character in binary_word:
            if binary_character == "0":
                if current_node.right_child:
                    xor_result += "1"
                    current_node = current_node.right_child
                else:
                    xor_result += "0"
                    current_node = current_node.left_child
            else:
                if current_node.left_child:
                    xor_result += "1"
                    current_node = current_node.left_child
                else:
                    xor_result += "0"
                    current_node = current_node.right_child

        maximum_xor_value = int(xor_result, 2)
        return maximum_xor_value

number_of_operations = int(input())

binary_trie = BinaryTrie()
initial_word = format(0, 'b').zfill(30)
binary_trie.insert_word(initial_word)

for _ in range(number_of_operations):
    operation_type, number = map(int, input().split())
    binary_word = format(number, 'b').zfill(30)

    if operation_type == 1:
        binary_trie.insert_word(binary_word)
    elif operation_type == 2:
        binary_trie.delete_word(binary_word)
    elif operation_type == 3:
        result = binary_trie.find_maximum_xor(binary_word)
        print(result)
