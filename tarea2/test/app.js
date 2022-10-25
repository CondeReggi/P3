(() => {
    const nodos = document.querySelector(".mat-chip-list-wrapper");
    let result = [];

    
    if(nodos && nodos.childNodes && nodos.childNodes.length !== 0) {
        for(let nodo of nodos.childNodes){
            if(nodo.childNodes.length !== 0){
                if([...nodo.classList].includes("mat-standard-chip")){
                    let value = nodo.innerText;
                    result.push(value.split(" ")[0]);
                }
            }
        }
        const value = result.map(x => x.split("\ncancel")[0]).join(" ");
        alert(value);
    }


})();