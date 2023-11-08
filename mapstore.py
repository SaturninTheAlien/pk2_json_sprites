#!/usr/bin/python3

# A script to download all the episodes from the old mapstore.

import json
import requests
from bs4 import BeautifulSoup

def download_file(url:str, filename:str)->None:
    response = requests.get(url)
    if response.status_code == 200:
        with open(filename, 'wb') as outfile:
            outfile.write(response.content)
        
        print("Done!")

    else:
        print("Cannot download the file, error code {}".format(response.status_code))

def download_episode(episode_data:dict)->None:
    if episode_data["name"] is None or episode_data["url"] is None:
        print("Cannot download nameless episode")
        return
    
    print("Downloading \"{}\"".format(episode_data["name"]))

    name_fixed = episode_data["name"].lower().replace(' ', '_')
    json_object = json.dumps(episode_data, indent=4)

    with open("mapstore/"+name_fixed+".json", "w") as outfile:
        outfile.write(json_object)

    download_file(episode_data["url"], "mapstore/"+name_fixed+".zip")

def scrap_episodes1(url:str)->None:
    r = requests.get(url)
    if r.status_code == 200:
        print(url)

        soup = BeautifulSoup(r.text, 'html.parser')
        main_table = soup.find("table")
        if main_table is not None:
            child_tables = main_table.find_all("table")
            for child_table in child_tables:
                trs = child_table.find_all("tr")

                episode_name = None
                author_name = None
                legacy_difficulty = None
                levels_number = None
                url = None
                description = None

                for tr in trs:    
                    
                    tds = tr.find_all("td")

                    if len(tds)<2:
                        description = tds[0].get_text().replace('\t', '').replace('\n', '').replace('  ', ' ')
                        continue

                    if tds[0].string=="Author:":
                        author_name = tds[1].string

                    elif tds[0].string=="Difficult:":
                        legacy_difficulty = tds[1].string

                    elif tds[0].string=="Maps:":
                        try:
                            levels_number = int(tds[1].string)

                        except:
                            pass

                    else:
                        link = tds[0].find("a")
                        if link is not None:
                            episode_name = link.string
                            url = link.get("href")

                if url is not None:
                    episode_data = {
                        "name": episode_name,
                        "author_name": author_name,
                        "legacy_difficulty": legacy_difficulty,
                        "levels_number": levels_number,
                        "url": url,
                        "description": description,
                    }
                    
                    download_episode(episode_data)

            
            pass
        else:
            print("Main table not found!")

    else:
        print("Unable to load website: {}".format(url))


def scrap_episodes2(url:str)->None:
    r = requests.get(url)
    if r.status_code == 200:
        print(url)

        soup = BeautifulSoup(r.text, 'html.parser')
        first_table = soup.find("table")
        if first_table is None:
            print("The first table not found")
            return
        
        second_table = first_table.find("table")
        if second_table is None:
            print("The second table not found")
            return
        
        trs = second_table.find_all("tr")
        for tr in trs:
            tds = tr.find_all("td")

            if len(tds) < 6:
                continue

            link = tds[0].find("a")
            if link is None:
                continue

            url = link.get("href")
            name = tds[0].text
            author_name = tds[1].text
            levels_number = None

            try:
                levels_number = int(tds[3].text)
            except:
                pass

            episode_data = {
                "url" :url,
                "name":name,
                "author_name":author_name,
                "levels_number":levels_number,
            }

            download_episode(episode_data)
    else:
        print("Unable to load website: {}".format(url))


def main():
    for i in range(2, 10):
        scrap_episodes1("http://mapstore.the.cz/index{}.html".format(i))

    scrap_episodes2("http://mapstore.the.cz/index10.html")

if __name__ == "__main__":
    main()
    pass
