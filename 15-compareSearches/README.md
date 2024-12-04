comparesearch result

<img width="692" alt="image" src="https://github.com/user-attachments/assets/395536b4-3cd9-4420-876b-e8440840e974">
<img width="696" alt="image" src="https://github.com/user-attachments/assets/a62618dd-43e6-4ab9-87e6-993fed0ac5d8">
<img width="773" alt="image" src="https://github.com/user-attachments/assets/89f0bd5f-5b8f-4ba8-8a02-3f52350b59fa">


결과분석
▪ A, B, C에 대해서 퀵 정렬후의 이진탐색에서 순차탐색보다 적게 비교하는 이유 

순차탐색은 정렬이 되었든 안 되었든 배열의 인덱스를 순차적으로 하나하나 방문하여 비교함(값이 배열 끝에 있을시에는 전체를 탐색해야함)
반면에 이진 탐색은 정렬된 배열에서만 사용이 가능함
퀵 정렬을 통해 배열을 정렬한 뒤 수행되는 이진 탐색은 중심 키를 기준으로 탐색 범위를 좁혀가며 비교를 진행하기 때문에 
당연히 순차탐색 보다 비교횟수가 적을 수 밖에 없음
