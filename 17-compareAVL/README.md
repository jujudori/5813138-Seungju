compare AVL result

<img width="379" alt="image" src="https://github.com/user-attachments/assets/e0179b5d-eed0-4bc7-b52e-d4c74588647a">

<img width="359" alt="image" src="https://github.com/user-attachments/assets/7202b5ba-fa59-40af-8a46-79e07dfb9c4e">
<img width="625" alt="image" src="https://github.com/user-attachments/assets/42a79f18-41eb-419a-892c-4ca62005ad07">



이진 탐색 트리와 AVL에 대한 탐색의 비교횟수 분석

1. 정리 

우선 bst를 기반으로 구현되는 AVL 트리는 삽입/삭제시 균형을 유지하여 탐색 성능이 O(log n)로 보장되는 반면, 
BST는 비균형 상태가 되면 최악의 경우 O(n)(경사트리인 경우) 까지 성능이 떨어진다.이 경우 순차 탐색과 같게 되어 효율이 아주 떨어진다. 
여기서 이진 탐색에서는 균형을 유지하는 것이 성능에서 무엇보다 중요하다는 것을 알 수 있다.

2.결과

코드 구현한 결과에서도 나타나는것이 보이는데, avl트리는 비교 횟수가 14-15인 반면 bst는 16-19, 혹은 그 이상 까지 avl보다 비교횟수가 많은 것을 알 수 있다.
이는 이진트리가 삽/삭시 균형을 잡지 않기때문에 탐색에서 비교횟수가 많이 걸리는 것으로 볼 수 있다. 
avl트리는 삽/삭시 바로바로 balancefactor로 불균형을 감지하고 회전을 이용하여 균형을 유지하도록 하기 때문에 탐색에서 bst보다 빠르게 탐색 하는 것을 볼 수 있다.


3.간단예시 

1,2,3,4,5 를 삽입 후 bst/avl 비교횟수 비교 


![image](https://github.com/user-attachments/assets/22f845e5-4b61-4473-8c6e-bcbfb410a62f)


5를 search할때 비교 횟수 avl = 1번 bst = 3번

4.결론 

avl이 bst에 비해 비교횟수가 적다(성능좋음) 
