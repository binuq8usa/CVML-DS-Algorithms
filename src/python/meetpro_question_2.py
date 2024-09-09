# Problem Description
# Given a list of synonym pairs, write a function to determine if a  pair of sentences are synonymous. 
# Two sentences are synonymous if you can match them (considering synonyms), word by word in order.

# synonyms = [(tac, cat) (dog, god)]
# set of su = [(tac,cat), (cat, tac)]
# sentence 1 = [a cat ate the dog abc] => 
# sentence 2 = [a tac ate the god cab] => fa

# sentence_1 =  [a ate the dog abc] => False => True
#                [a ate the god abc]

# sent -> list of words


# * Number of synonym pairs - N
# * Number of words in a sentence - K
# synonum

# [(happy, joy), (happy, elation)] -> (joy, elation)
# [(joy, happy), (elation, happy)] -> (joy, elation)

# [(a, b) (b, c) (c, d)] -> (a,c) ; (b,d)
# [(a,b) (c,d) (b,c)] - 
# iteration 1 : [(a,b), (c,d) (b,c)] => (a,d) (b,d) =>     (a,c), (b,d) => (a,c) (b,d)
# M dif ->
# 
#  -> (a, d)


from typing import List, Tuple, Set, Optional, Dict, Deque
from collections import Counter, defaultdict, OrderedDict, deque

class WordGraph:
    def __init__(self) -> None:
        self.num_words : int = 0
        self.list_of_words : List[str] = []
        self.adjacency_list : Dict[str, List[str]] = defaultdict(list)
        self.word_ids : Dict[str, int] = OrderedDict()
    
    def add_edge(self,word_u : str, word_v: str) -> None:
        self.adjacency_list[word_u].append(word_v)
        self.adjacency_list[word_v].append(word_u)

    def populate_graph(self,word_pairs : List[Tuple[str, str]]):
        for word_u, word_v in word_pairs:
            self.add_edge(word_u, word_v) 
        self.list_of_words = sorted(list(self.adjacency_list.keys()))
        self.num_words = len(self.list_of_words)
        self.word_ids = OrderedDict.fromkeys(self.list_of_words)

    # connected component dfs 
    def get_conn_comp(self):
        set_of_explored_words = set()

        for idx,word in enumerate(self.list_of_words):
            if word not in set_of_explored_words:
                self._dfs(parent_word=word, parent_id=idx, set_of_explored=set_of_explored_words)
                
    def _dfs(self, parent_word : str, parent_id :int, set_of_explored : Set):
        stack : Deque = deque()
        stack.append(parent_word)

        while bool(stack):
            curr_word = stack[-1]
            if curr_word not in set_of_explored:
                set_of_explored.add(curr_word)
                self.word_ids[curr_word] = parent_id
            
                for n_word in self.adjacency_list[curr_word]:
                    if n_word not in set_of_explored:
                        stack.append(n_word)
            else:
                stack.pop()

def test_word_graph():
    graph : WordGraph = WordGraph()
    synonyms = [
        ("happy", "elated"),
        ("estatic", "happy"),
        ("sad", "depressed"),
        ("angry", "sad"),
        ("energetic", "strong"),
        ("strong", "levelheaded")
    ]

    graph.populate_graph(synonyms)
    graph.get_conn_comp()
    print(f'ids : {graph.word_ids}')

test_word_graph()

def merge_synonynm_pair(list_sn: List[Tuple[str]]) -> List[Tuple[str]]:
    new_syn_pair_list : List[Tuple[str,str]] = list_sn
    org_len = len(new_syn_pair_list)
    while True:
        merged_list = []
        for idx_1 in range(0, len(list_sn)-1):
            for idx_2 in range(idx_1+1, len(list_sn)):
                new_syn_pair = compare_synonym_pair(list_sn[idx_1], list_sn[idx_2])
            if new_syn_pair:
                merged_list.append(new_syn_pair)
    
def compare_synonym_pair(pair_1, pair_2) -> Optional[Tuple[str, str]]:
    list_of_words = list(pair_1)
    list_of_words.extend(list(pair_2)) # 4
    counter = Counter(list_of_words) # 2, 1, 1 otherwise 1,1 1,1
    synonym_pair = []
    for word, count in counter.items():
        if count == 1:
            synonym_pair.append(word)

    synonym_pair = tuple(synonym_pair) if len(synonym_pair) == 2 else None
    return synonym_pair
    
def are_two_sents_synonymous(synonyms : List[Tuple[str,str]], first_sent : List[str], second_sent: List[str]) -> bool:
    if len(first_sent) != len(second_sent):
        return False 

    if first_sent == second_sent: # O(K)
        return True

    set_of_synonyms : Set[Tuple[str,str]] = set() 
    for sn1, sn2 in synonyms: # O(N)
        set_of_synonyms.add((sn1, sn2))
        set_of_synonyms.add((sn2, sn1))

    # pair comparison between synonym entries - O(M*M) or O(M log M)
    is_synonymous : bool = True
    for word_1, word_2 in zip(first_sent, second_sent): # O(K)
        if word_1 == word_2:
            continue
        if (word_1, word_2) not in set_of_synonyms: # O(1)
            is_synonymous = False
            break

    # run time - O(N + K)
    return is_synonymous




