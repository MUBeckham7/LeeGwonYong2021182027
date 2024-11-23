import requests

# API 키 설정 (실제 사용 시 환경 변수를 사용하는 것이 안전합니다)
headers = {
    "x-nxopen-api-key": "test_edf174873c1ad589de2a20a8e711635ff8bda0098e5350ac4f6da7fce74f5e96efe8d04e6d233bd35cf2fabdeb93fb0d"  # 실제 사용 시 주의!
}

characterName = "MUFC바비찰튼"
id_url = "https://open.api.nexon.com/fconline/v1/id"

# Step 1: OUID 가져오기
params_id = {
    "nickname": characterName
}

response_id = requests.get(id_url, headers=headers, params=params_id)

if response_id.status_code == 200:
    data_id = response_id.json()
    ouid = data_id.get('ouid')  # 실제 키 이름 확인 필요
    if ouid:
        print(f"OUID: {ouid}")
        
        # Step 2: OUID를 사용하여 기본 정보 조회
        user_basic_url = "https://open.api.nexon.com/fconline/v1/user/basic"
        params_basic = {
            "ouid": ouid
        }
        response_basic = requests.get(user_basic_url, headers=headers, params=params_basic)
        
        if response_basic.status_code == 200:
            data_basic = response_basic.json()
            print("기본 정보 조회 성공:")
            print(data_basic)
        else:
            print("기본 정보 조회에 실패했습니다:")
            print(response_basic.json())
    else:
        print("응답에서 'ouid'를 찾을 수 없습니다.")
        print(data_id)
else:
    print("OUID를 가져오는 데 실패했습니다:")
    print(response_id.json())