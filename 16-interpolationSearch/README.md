interpolation result 


<img width="854" alt="image" src="https://github.com/user-attachments/assets/6849a0e0-42bb-4b92-ac74-9ce607c33324">
<img width="742" alt="image" src="https://github.com/user-attachments/assets/58e57623-112f-46b0-8c97-81ac95ae1074">
<img width="826" alt="image" src="https://github.com/user-attachments/assets/370eb35b-46ec-4692-af8f-7c32554182dc">


  

Interpolation Search가 Binary Search보다 적게 비교하는 이유를 설명

그 이유는 보간 탐색이 값의 분포를 고려하기 때문임
이진 탐색은 항상 배열의 중간을 기준으로 비교하는 반면, 보간 탐색은 배열에서 목표 값이 있을 가능성이 높은 위치를 예측하여 탐색을 시작함.
보간 탐색은 배열이 정렬되어 있다고 가정할 때, 목표 값이 있을 것으로 예상되는 위치를 계산 > 이를 위해 목표 값과 배열의 첫 번째, 마지막 값을 이용하여 예상 위치를 구함 
이 과정에서 목표 값이 위치할 가능성이 높은 곳을 바로 찾으려 하고, 중간 값을 기준으로 한 비교보다는 더 효율적인 경우가 많음
반면, 이진 탐색은 항상 배열의 중간 값을 기준으로 비교하므로, 값의 분포에 관계없이 매번 중간 값을 비교함 
탐색 크기를 줄일 수 있으나 위치가능성 높은 곳을 바로 찾는 보간 탐색보다는 비효율적임

결론 : 값이 특정 구간에 몰려 있거나, 목표 값이 배열의 끝에 가까운 경우, 보간 탐색은 더 빠르게 목표 값을 찾을 수 있음.
보간 탐색은 배열의 값들이 균등하게 분포되어 있을 때 제일 효율적임 
