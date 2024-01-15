import requests

def download_file(url, destination):
    response = requests.get(url)
    if response.status_code == 200:
        with open(destination, 'wb') as file:
            file.write(response.content)
        print(f"Downloaded successfully to {destination}")
    else:
        print(f"Failed to download. Status code: {response.status_code}")


url = 'https://media4.giphy.com/media/UnyblOs6hGx9Mli7jq/giphy.gif?cid=ecf05e47v0h8ivyoevypldgcut1l0261zdiopkhmjk60g4io&ep=v1_gifs_related&rid=giphy.gif&ct=s'
destination = 'happysun.gif'
download_file(url, destination)