출력결과



<img width="817" alt="image" src="https://github.com/user-attachments/assets/c6a41f14-ff9a-474f-824f-0c2573d2e004">
<img width="793" alt="image" src="https://github.com/user-attachments/assets/5cd00fe6-c6d7-4d3f-9a5f-9f73e597380e">
<img width="876" alt="image" src="https://github.com/user-attachments/assets/6bb89ba6-61a5-4878-9763-7a4672b4dab7">



결과분석
▪ A, B, C에 대해서 퀵 정렬후의 이진탐색에서 순차탐색보다 적게 비교하는 이유 

순차탐색은 정렬이 되었든 안 되었든 배열의 인덱스를 순차적으로 하나하나 방문하여 비교한다(값이 배열 끝에 있을시에는 전체를 탐색해야함)
반면에 이진 탐색은 정렬된 배열에서만 사용이 가능하다
퀵 정렬을 통해 배열을 정렬한 뒤 수행되는 이진 탐색은 중심 키를 기준으로 탐색 범위를 좁혀가며 비교를 진행하기 때문에 
당연히 순차탐색 보다 비교횟수가 적을 수 밖에 없다.
