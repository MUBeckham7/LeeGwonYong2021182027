import requests

headers = {
    "x-nxopen-api-key": "test_edf174873c1ad589de2a20a8e711635ff8bda0098e5350ac4f6da7fce74f5e96efe8d04e6d233bd35cf2fabdeb93fb0d"
}

characterName = "MUFC바비찰튼"
url = "https://open.api.nexon.com/fconline/v1/id"

params = {
    "nickname": characterName
}

response = requests.get(url, headers=headers, params=params)

print(response.json())