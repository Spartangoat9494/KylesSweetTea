document.addEventListener('DOMContentLoaded', function () {
    // Smooth Scroll for Navigation Links
    var navLinks = document.querySelectorAll('.nav-links a');
    navLinks.forEach(function (link) {
        link.addEventListener('click', function (e) {
            e.preventDefault(); // Prevent default navigation behavior
            
            // Get the target ID from href
            var targetId = this.getAttribute('href').substring(1);
            var targetElement = document.getElementById(targetId);
            
            // If the target element exists, scroll to it
            if (targetElement) {
                window.scrollTo({
                    top: targetElement.offsetTop,
                    behavior: 'smooth'
                });
            }
        });
    });

    var cart = [];
    var cartItemsContainer = document.getElementById('cartItems');
    var totalPriceElement = document.getElementById('totalPrice');

    // Add to cart function
    function addToCart(serviceName, price) {
        cart.push({ serviceName: serviceName, price: price });
        updateCartDisplay();
    }

    // Update the cart display (list of items + total price)
    function updateCartDisplay() {
        var cartItemsList = cart.map(function (item) {
            return '<li>' + item.serviceName + ' - $' + item.price.toFixed(2) + '</li>';
        }).join('');
        
        var total = cart.reduce(function (total, item) {
            return total + item.price;
        }, 0).toFixed(2);

        // Update the cart display area
        cartItemsContainer.innerHTML = cartItemsList;
        totalPriceElement.textContent = 'Total: $' + total;
    }

    // Clear the cart
    function clearCart() {
        cart = [];
        updateCartDisplay();
    }

    // Add event listeners for add-to-cart buttons on each service
    var addToCartButtons = document.querySelectorAll('.add-to-cart');
    addToCartButtons.forEach(function (button) {
        button.addEventListener('click', function () {
            var serviceName = button.closest('.card').querySelector('h3').textContent;
            var price = parseFloat(button.closest('.card').querySelector('.price').textContent.replace('$', ''));
            addToCart(serviceName, price);
        });
    });
});
