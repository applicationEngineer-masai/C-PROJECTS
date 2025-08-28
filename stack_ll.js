

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class Stack {
    constructor() {
        this.top = null; // head of linked list
        this.size = 0; // size
    }

    push(x) {
        let newNode = new Node(x);
        newNode.next = this.top;
        this.top = newNode;
        this.size++;
    }

    pop() {
        if(this.isEmpty()) {
            console.log("Stack Underflow");
            return null;
        }
        let val = this.top.data;
        this.top = this.top.next;
        this.size--;
        return val;
    }

    peek() {
        return (this.isEmpty()) ? null : this.top.data;
    }

    isEmpty() {
        return this.top == null;
    }

    getSize() {
        return this.size;
    }

    printStack() {
        let curr = this.top;
        let out = [];

        while(curr) {
            out.push(curr.data);
            curr = curr.next;
        }

        console.log("Stack : ", out.join(" -> "));
    }
}

let st = new Stack();

st.push(10);
st.push(20);
st.push(30);
st.push(12);
st.push(8);

st.printStack();

console.log("Top:", st.peek());  
console.log("Popped:", st.pop());
console.log("Top:", st.peek());  
st.printStack();                 