class Node:
	def __init__(self, depth: int):
		self.nodes = {}
		self.depth = depth
		self.terminate = False

	def add(self, word: str):
		if len(word) == self.depth:
			self.terminate = True
		else:
			if word[self.depth] not in self.nodes:
				self.nodes[word[self.depth]] = Node(self.depth + 1)
			self.nodes[word[self.depth]].add(word)

	def check(self, word: str):
		if self.terminate:
			return self.depth
		if len(word) == self.depth or word[self.depth] not in self.nodes:
			return -1
		return self.nodes[word[self.depth]].check(word)


class Bor:
	def __init__(self):
		self.nodes = {}

	def add(self, word: str):
		if word[0] not in self.nodes:
			self.nodes[word[0]] = Node(1)
		self.nodes[word[0]].add(word)

	def check(self, word: str):
		if word[0] not in self.nodes:
			return -1
		return self.nodes[word[0]].check(word)


bor = Bor()
for i in input().split():
	bor.add(i)
for i in input().split():
	temp = bor.check(i)
	if temp == -1:
		print(i, end=" ")
	else:
		print(i[:temp], end=" ")
