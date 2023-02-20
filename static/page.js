async function crawlPageSelector() {
	const stylesRequest = await fetch("static/styles.css");
	const styles = await stylesRequest.text();
	const lines = styles.split("\n");

	// Look for where counter-increment: page is.
	const c = lines.findIndex(line => line.includes("counter-increment: page"));

	// Look for the selector that comes before it.
	let s;
	let e;
	for (let i = c - 1; i != 0 && (!s || !e); i--) {
		if (lines[i].includes("{")) {
			// We've crawled up to the start of our CSS block, which is the end
			// of our selector.
			e = i + 1;
			continue;
		}
		if (lines[i].includes("}")) {
			// We've crawled up to the end of another CSS block, which is the
			// start of our selector.
			s = i + 1;
			continue;
		}
	}

	return lines
		.slice(s, e)
		.join("\n")
		.replace(/[{}]/g, "")
		.trim();
}

function countPages(pageSelector) {
	const pages = document.querySelectorAll(pageSelector);
	const pageMap = new Map();
	
	// Manually count the pages into pageMap.
	let counter = 0;
	for (const page of pages) {
		counter++;
		if (page.id) {
			pageMap.set(page.id, counter);
		}
	}

	return pageMap;
}

const selector = await crawlPageSelector();
const pageMap = countPages(selector);

const tocLinks = document.querySelectorAll("#toc li a[href^='#']");
for (const link of tocLinks) {
	const href = link.getAttribute("href");
	const page = pageMap.get(href.slice(1));
	if (page) {
		link.setAttribute("data-page", pageMap.get(href.slice(1)));
	}
}
