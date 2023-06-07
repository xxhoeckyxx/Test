function inizializingPage(){
    getNavbar();
    getFooter();
}

function getNavbar(){
    fetch('common.html')
        .then(response => response.text())
        .then(html => {
            const parser = new DOMParser();
            const doc = parser.parseFromString(html, 'text/html');
            const commonContent = doc.documentElement;
    
            const navbar = document.querySelector('div');
            navbar.innerHTML = commonContent.querySelector('div').innerHTML;

        });
}

function getFooter(){
    fetch('common.html')
        .then(response => response.text())
        .then(html => {
            const parser = new DOMParser();
            const doc = parser.parseFromString(html, 'text/html');
            const commonContent = doc.documentElement;

            const footer = document.querySelector('#footer');
            footer.innerHTML = commonContent.querySelector('footer').innerHTML;
        });
}