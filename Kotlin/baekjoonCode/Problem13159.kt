import kotlin.math.*

fun main() {
    var inputLine = readLine()!!.split(' ')
    var numberOfElements = inputLine[0].toInt()
    var numberOfQueries = inputLine[1].toInt()

    var elementsArray = LongArray(numberOfElements) { i -> i + 1L }
    var splayTree = SplayTree(numberOfElements, elementsArray)

    var resultBuilder = StringBuilder()
    for (queryIndex in 0 until numberOfQueries) {
        inputLine = readLine()!!.split(' ')
        var operation = inputLine[0].toInt()
        when (operation) {
            1 -> {
                var left = inputLine[1].toInt()
                var right = inputLine[2].toInt()
                var rangeResult = splayTree.getRange(left, right)
                resultBuilder.append(rangeResult.min).append(' ').append(rangeResult.max).append(' ').append(rangeResult.sum).append('\n')

                splayTree.reverseRange(left, right)
            }
            2 -> {
                var left = inputLine[1].toInt()
                var right = inputLine[2].toInt()
                var rangeResult = splayTree.getRange(left, right)
                resultBuilder.append(rangeResult.min).append(' ').append(rangeResult.max).append(' ').append(rangeResult.sum).append('\n')

                var shiftValue = inputLine[3].toLong()
                shiftValue += (right - left + 1) * 300000L
                shiftValue %= (right - left + 1)
                if (shiftValue == 0L) continue
                splayTree.reverseRange(left, right)
                splayTree.reverseRange(left, left + shiftValue.toInt() - 1)
                splayTree.reverseRange(left + shiftValue.toInt(), right)
            }
            3 -> {
                var index = inputLine[1].toInt()
                splayTree.selectKthElement(index)
                resultBuilder.append(splayTree.root!!.key).append('\n')
            }
            4 -> {
                var index = inputLine[1].toInt()
                splayTree.splay(splayTree.nodePointers[index]!!)
                resultBuilder.append(splayTree.root!!.leftChild!!.count).append('\n')
            }
        }
    }
    for (i in 1..numberOfElements) {
        splayTree.selectKthElement(i)
        resultBuilder.append(splayTree.root!!.key).append(' ')
    }
    print(resultBuilder)
}

class Node(var key: Long) {
    var leftChild: Node? = null
    var rightChild: Node? = null
    var parent: Node? = null
    var count = 0
    var min = 0L
    var max = 0L
    var sum = 0L
    var isDummy = false
    var needsFlip = false
}

class SplayTree(numberOfNodes: Int, initialValues: LongArray) {
    var root: Node? = null
    var nodePointers = Array<Node?>(numberOfNodes + 2) { null }

    init {
        var currentNode = Node(0L)
        root = currentNode
        nodePointers[0] = currentNode
        for (i in 0 until numberOfNodes) {
            currentNode.rightChild = Node(initialValues[i])
            currentNode.rightChild!!.parent = currentNode
            currentNode = currentNode.rightChild!!
            nodePointers[i + 1] = currentNode
        }
        currentNode.rightChild = Node(0L)
        currentNode.rightChild!!.parent = currentNode
        nodePointers[numberOfNodes + 1] = currentNode.rightChild
        root!!.isDummy = true
        currentNode.rightChild!!.isDummy = true
        for (i in numberOfNodes + 1 downTo 0) update(nodePointers[i]!!)
        splay(nodePointers[numberOfNodes / 2]!!)
    }

    fun rotate(node: Node) {
        if (node.parent == null) return
        var parentNode = node.parent
        var childNode: Node?
        propagateFlip(parentNode!!)
        propagateFlip(node)
        if (node == parentNode!!.leftChild) {
            childNode = node.rightChild
            parentNode.leftChild = childNode
            node.rightChild = parentNode
        } else {
            childNode = node.leftChild
            parentNode.rightChild = childNode
            node.leftChild = parentNode
        }
        node.parent = parentNode.parent
        parentNode.parent = node
        if (childNode != null) childNode.parent = parentNode
        if (node.parent != null) {
            if (parentNode == node.parent!!.leftChild) node.parent!!.leftChild = node
            else node.parent!!.rightChild = node
        } else root = node
        update(parentNode)
        update(node)
    }

    fun splay(node: Node, targetParent: Node? = null) {
        while (node.parent != targetParent) {
            var parentNode = node.parent
            if (parentNode!!.parent == targetParent) {
                rotate(node)
                break
            }
            var grandParentNode = parentNode.parent
            rotate(if ((parentNode.leftChild == node) == (grandParentNode!!.leftChild == parentNode)) parentNode else node)
            rotate(node)
        }
        if (targetParent == null) root = node
    }

    fun update(node: Node) {
        node.count = 1
        node.min = node.key
        node.max = node.key
        node.sum = node.key
        if (node.leftChild != null) {
            node.count += node.leftChild!!.count
            node.min = min(node.min, node.leftChild!!.min)
            node.max = max(node.max, node.leftChild!!.max)
            node.sum += node.leftChild!!.sum
        }
        if (node.rightChild != null) {
            node.count += node.rightChild!!.count
            node.min = min(node.min, node.rightChild!!.min)
            node.max = max(node.max, node.rightChild!!.max)
            node.sum += node.rightChild!!.sum
        }
    }

    fun selectKthElement(k: Int) { // 0-based
        var currentNode = root
        propagateFlip(currentNode!!)
        var tempK = k
        while (true) {
            while (currentNode!!.leftChild != null && currentNode.leftChild!!.count > tempK) {
                currentNode = currentNode.leftChild
                propagateFlip(currentNode!!)
            }
            if (currentNode.leftChild != null) tempK -= currentNode.leftChild!!.count
            if (tempK-- == 0) break
            currentNode = currentNode.rightChild
            propagateFlip(currentNode!!)
        }
        splay(currentNode!!)
    }

    fun getRange(start: Int, end: Int): Node {
        selectKthElement(end + 1)
        var tempNode = root
        selectKthElement(start - 1)
        splay(tempNode!!, root)
        return root!!.rightChild!!.leftChild!!
    }

    fun propagateFlip(node: Node) {
        if (!node.needsFlip) return
        var tempNode = node.leftChild
        node.leftChild = node.rightChild
        node.rightChild = tempNode
        if (node.leftChild != null) node.leftChild!!.needsFlip = !node.leftChild!!.needsFlip
        if (node.rightChild != null) node.rightChild!!.needsFlip = !node.rightChild!!.needsFlip
        node.needsFlip = false
    }

    fun reverseRange(start: Int, end: Int) {
        var node = getRange(start, end)
        node.needsFlip = !node.needsFlip
    }
}
