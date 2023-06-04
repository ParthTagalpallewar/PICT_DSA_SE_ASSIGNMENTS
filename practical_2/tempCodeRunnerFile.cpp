
    Queue<int> q(10e5);

    for(int i=0; i<10; i++){
        q.enqueue(i);
    }

    while(!q.is_empty()){
        cout << q.dequeue() << endl;
    }

    return 0;