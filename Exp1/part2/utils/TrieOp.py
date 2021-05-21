from typing import Tuple
from collections import deque

class TrieNode(object):
    """
    Our trie node implementation. Very basic. but does the job
    """
    state = 500
    def __init__(self, char: str):
        self.char = char
        self.children = []
        # Is it the last character of the word.`
        self.word_finished = False
        # How many times this character appeared in the addition process
        self.counter = 1
        self.state = TrieNode.state
        TrieNode.state += 1
    

    def add(root, word: str):
        """
        Adding a word in the trie structure
        """
        node = root
        for char in word:
            found_in_child = False
            # Search for the character in the children of the present `node`
            for child in node.children:
                if child.char == char:
                    # We found it, increase the counter by 1 to keep track that another
                    # word has it as well
                    child.counter += 1
                    # And point the node to the child that contains this char
                    node = child
                    found_in_child = True
                    break
            # We did not find it so add a new chlid
            if not found_in_child:
                new_node = TrieNode(char)
                node.children.append(new_node)
                # And then point node to the new child
                node = new_node
        # Everything finished. Mark it as the end of a word.
        node.word_finished = True


    def find_prefix(root, prefix: str) -> Tuple[bool, int]:
        """
        Check and return 
        1. If the prefix exsists in any of the words we added so far
        2. If yes then how may words actually have the prefix
        """
        node = root
        # If the root node has no children, then return False.
        # Because it means we are trying to search in an empty trie
        if not root.children:
            return False, 0
        for char in prefix:
            char_not_found = True
            # Search through all the children of the present `node`
            for child in node.children:
                if child.char == char:
                    # We found the char existing in the child.
                    char_not_found = False
                    # Assign node as the child containing the char and break
                    node = child
                    break
            # Return False anyway when we did not find a char.
            if char_not_found:
                return False, 0
        # Well, we are here means we have found the prefix. Return true to indicate that
        # And also the counter of the last node. This indicates how many words have this
        # prefix
        return True, node.counter



def ifTemplate(state, curr, i):
    w = "else"
    if i == 0: 
        w = ""
    return "\n\t" + w + " if (curr == '"+ str(curr) +"'){\n\t\tstrncat(lexeme, &curr, 1);\n\t\tstate = "+ str(state) +"; // <===\n\t}"

def endTemplate(isKeyword, n):
    if n == 0:
        return '\n\tresetLexeme("operator");\n\tstate = resetState(curr);\n'
    return '\n\telse {\n\t\tresetLexeme("operator");\n\t\tstate = resetState(curr);\n\t}'

def caseTemplate(node: TrieNode):
    res = f"case {node.state}: // {node.char}\n\tcurr = getNextChar();\n"
    for i, child in enumerate(node.children):
        res += ifTemplate(child.state, child.char, i)
    res += endTemplate(node.word_finished, len(node.children))

    res += "\n\tbreak;\n"
    return res


def bfs(root: TrieNode, file, statesList):
    que = deque()
    que.append(root)
    while que:
        node = que.popleft()
        statesList.append((node.state, node.char))
        file.write(caseTemplate(node))
        for child in node.children:
            que.append(child)


if __name__ == "__main__":
    root = TrieNode('*')
    # keys = ['and', 'array', 'begin', 'case', 'const', 'div', 'do', 'downto', 'else', 'end', 'file', 'for', 'function', 'goto', 'if', 'in', 'label', 'mod', 'nil', 'not', 'of', 'packed', 'procedure', 'program', 'record', 'repeat', 'set', 'then', 'to', 'type', 'uses', 'until', 'var', 'while', 'with']
    keys = ['..', '[', ']', ':=', '+', '-', '*', '/', '%', '&', '|', '!', '<<', '>>', '~', '<=', '=<', '=>', '>=', '<>', '=', '<', '>']
    
    for key in keys:
        root.add(key)

    statesList = []

    file = open("outputOp.rud", "a")
    for child in root.children:
        print(f"case '{child.char}':\n\tstrncat(lexeme, &curr, 1);\n\treturn {child.state};")
        bfs(child, file, statesList)
    file.close()

    stateFile = open("stateOp.rud", "a")
    for s, c in statesList:
        stateFile.write(f"{s}\t{c}\n")
    stateFile.close()
    # print(endTemplate(True))

